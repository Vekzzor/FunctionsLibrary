#pragma once

#pragma warning (disable : 4215 4267 4305)
#include "MathFunc.h"
#include "Graph.h"
#include "Sorting.h"
#include "PriorityQueue.h"
#include <algorithm>
#include <string>
#include <vector>
#include <iostream>
#include <DirectXMath.h>
#include <d3d11.h>
#include <bits.h>

#ifdef _DEBUG
#define DBG_NEW new ( _NORMAL_BLOCK , __FILE__ , __LINE__ )
#else
#define new new
#endif