/*-----------------------------------------------------------------------
Licensed to the Apache Software Foundation (ASF) under one
or more contributor license agreements.  See the NOTICE file
distributed with this work for additional information
regarding copyright ownership.  The ASF licenses this file
to you under the Apache License, Version 2.0 (the
"License"; you may not use this file except in compliance
with the License.  You may obtain a copy of the License at

  http://www.apache.org/licenses/LICENSE-2.0

Unless required by applicable law or agreed to in writing,
software distributed under the License is distributed on an
"AS IS" BASIS, WITHOUT WARRANTIES OR CONDITIONS OF ANY
KIND, either express or implied.  See the License for the
specific language governing permissions and limitations
under the License.
-----------------------------------------------------------------------*/
/*-----------------------------------------------------------------------
From Scott Meyers C++ book
-----------------------------------------------------------------------*/

#pragma once

#if __cplusplus < 201103L

///< It is a const object...
const
class nullptr_t
{
  public:

    /**
     * T* casting operator
     *
     * @returns	The result of the operation.
     */
    template<class T>
    inline operator T*() const // convertible to any type of null non-member pointer...
    { return 0; }

    /**
     * Gets the *
     *
     * @tparam	C	Type of the c.
     * @tparam	T	Generic type parameter.
     *
     * @returns	A T.
     */
    template<class C, class T>
    inline operator T C::*() const   // or any type of null member pointer...
    { return 0; }

  private:
    /** Reference operator */
    void operator&() const;  // Can't take address of nullptr

///< .
} nullptr = {};

#endif

