#ifndef ECS_H
#define ECS_H
#include <bitset>
#include <vector>
#include <unordered_map>
#include <typeindex>
#include <set>

const unsigned int MAX_COMPONENTS = 32;
///////////////////////////////////////////////////////////////////////////
// Signature
///////////////////////////////////////////////////////////////////////////
// We use a bitset to keeo track of which components en entity has
// and also helps keep track of which entities a system is interested in
///////////////////////////////////////////////////////////////////////////
typedef std::bitset<MAX_COMPONENTS> Signature;

// I == Base
struct IComponent
{
protected:
  static int nextId;
};

// Used to assign a unique id to a component type
// NOTE: No class yet due to template
template <typename TComponent>
class Component : public IComponent
{
public:
  static int GetId()
  {
    static auto id = nextId++;
    return id;
  }

private:
};

class Entity
{
public:
  Entity(int id) : id{id} {};
  Entity(const Entity &entity) = default;
  int GetId() const;

  Entity &operator=(const Entity &other) = default;
  bool operator==(const Entity &other) const { return id == other.id; };
  bool operator!=(const Entity &other) const { return id != other.id; };
  bool operator>(const Entity &other) const { return id > other.id; };
  bool operator<(const Entity &other) const { return id < other.id; };

private:
  int id;
};

// NOTE:The system process entities that contain a specific signature
class System
{
public:
  System() = default;
  virtual ~System() = default;

  void AddEntityToSystem(Entity entity);
  void RemoveEntityFromSystem(Entity entity);
  std::vector<Entity> GetSystemEntities() const;
  const Signature &GetComponentSignature() const;

  // Defines the component type that entities must have to be
  // considered by the system
  template <typename TComponent>
  void RequireComponent();

private:
  Signature componentSignature;
  std::vector<Entity> entities;
};

///////////////////////////////////////////////////////////////////////////
// Pool
///////////////////////////////////////////////////////////////////////////
// A pool is just a vector (contiguous data) of objects of type T
///////////////////////////////////////////////////////////////////////////
class IPool
{
  virtual ~IPool() {}
};

template <typename T>
class Pool : public IPool
{
private:
  std::vector<T> data;

public:
  Pool(int size = 100)
  {
    data.resize(size);
  }

  virtual ~Pool() = default;

  bool isEmpty() const
  {
    return data.empty();
  }

  int GetSize() const
  {
    return data.size();
  }

  void Resize(int n)
  {
    data.resize(n);
  }

  void Clear()
  {
    data.clear();
  }

  void Add(T obj)
  {
    data.push_back(obj);
  }

  void Set(int index, T obj)
  {
    data[index] = obj;
  }

  T &Get(int index)
  {
    return static_cast<T &>(data[index]);
  }

  T &operator[](unsigned int index)
  {
    return data[index];
  }
};

///////////////////////////////////////////////////////////////////////////
// Registry
///////////////////////////////////////////////////////////////////////////
// The Registry manages the creation and destruction of entities, as
// well as adding systems and adding components to entities.
///////////////////////////////////////////////////////////////////////////
class Registry
{
public:
  Registry() = default;

  Entity CreateEntity();

  // TODO: AddComponent<T>();

  void AddEntityToSystem(Entity entity);

private:
  int numEntities = 0;
  // how many entities attached to this component
  std::vector<IPool *> componentPools;
  // which component is turned on for which entity
  std::vector<Signature> entityComponentSignatures;
  // Key Value pair
  std::unordered_map<std::type_index, System *> systems;
  // Set of entities that are flagged to be added or removed in the next registry Update()
  std::set<Entity> entitiesToBeAdded;
  std::set<Entity> entitiesToBeKilled;
};

template <typename TComponent>
void System::RequireComponent()
{
  const auto componentId = Component<TComponent>::GetId();
  componentSignature.set(componentId);
}

#endif