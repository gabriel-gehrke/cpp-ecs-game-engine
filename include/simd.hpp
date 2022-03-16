#pragma once

typedef float float2 __attribute__ ((vector_size (8)));
typedef float2 vec2;
typedef float float4 __attribute__ ((vector_size (16)));
typedef float4 vec4;

float sqrlength2(float2& vec);
float length2(float2& vec);

float sqrlength3(float4& vec);
float length3(float4& vec);