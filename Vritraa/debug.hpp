#pragma once
#include "mutex.hpp"
#include "AutoLock.hpp"

#ifndef NDEBUG
#define NDEBUG false
#else
#define NDEBUG true
#endif

#ifndef DEBUG
#define DEBUG !NDEBUG
#endif