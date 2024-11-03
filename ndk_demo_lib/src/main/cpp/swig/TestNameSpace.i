//%module(javabegin="import com.example.ndk_demo_lib1.*;"
//                  "\nimport com.example.ndk_demo_lib1.*;") TestNameSpace

%import "namespace_config.i"

%nsp_2_java_6(TestNameSpace, com.example.ndk_demo_lib1,
      com.example.ndk_demo_lib1.*,
      com.example.ndk_demo_lib2.*,
      com.example.ndk_demo_lib3.*,
      com.example.ndk_demo_lib4.*,
      com.example.ndk_demo_lib5.*,
      com.example.ndk_demo_lib6.*
)
//%namespace_java(TestNameSpace, com.example.ndk_demo_lib1)

//%module(javabegin="package PACKAGE;") TestNameSpace

%typemap(javaimports) TestNameSpace %{
package com.example.ndk_demo_lib1.xxx;

import com.example.ndk_demo_lib1.*;
%}



%{
#include "TestNameSpace.h"
%}

%pragma(java) jniclassimports=%{
import com.example.ndk_demo_lib1.*;
%}


%include "TestNameSpace.h"


// swig -c++ -java -package com.example.ndk_demo_lib1 -directors TestNameSpace.txt