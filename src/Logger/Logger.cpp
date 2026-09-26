#include "Logger.h"
#include <chrono>
#include <ctime>
#include <iostream>
#include <stdio.h>

std::vector<LogEntry> Logger::messages;

static void SetColor(int textColor)
{
  // Octal: 033
  std::cout << "\x1B[" << textColor << "m";
}

static void ResetColor()
{
  // Octal: 033
  std::cout << "\x1B[0m";
}

void Logger::Log(const std::string &message)
{
  std::chrono::time_point<std::chrono::system_clock> now;
  now = std::chrono::system_clock::now();

  std::time_t result = std::chrono::system_clock::to_time_t(now);
  char timeString[std::size("dd/mm/yyyy hh:mm:ss")];
  std::strftime(std::data(timeString), std::size(timeString), "%d/%m/%Y %H:%M:%S", std::localtime(&result));

  LogEntry logEntry;
  logEntry.type = LOG_INFO;
  logEntry.message = std::string("LOG : [ ") + timeString + " ] - " + message;

  SetColor(32);
  std::cout << "LOG : [ " << timeString << " ] - " << message;
  ResetColor();

  messages.push_back(logEntry);
}

void Logger::Err(const std::string &message)
{
  std::chrono::time_point<std::chrono::system_clock> now;
  now = std::chrono::system_clock::now();

  std::time_t result = std::chrono::system_clock::to_time_t(now);
  char timeString[std::size("dd-mm-yyyy hh:mm:ss")];
  std::strftime(std::data(timeString), std::size(timeString), "%d/%m/%Y %H:%M:%S", std::localtime(&result));

  LogEntry logEntry;
  logEntry.type = LOG_ERROR;
  logEntry.message = std::string("ERR : [ ") + timeString + " ] - " + message;

  SetColor(31);
  std::cout << "ERR : [ " << timeString << " ] - " << message;
  ResetColor();

  messages.push_back(logEntry);
}