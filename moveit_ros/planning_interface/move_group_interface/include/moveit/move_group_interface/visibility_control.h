// Copyright (c) 2021, Open Source Robotics Foundation, Inc.
// All rights reserved.
//
// Software License Agreement (BSD License 2.0)
//
// Redistribution and use in source and binary forms, with or without
// modification, are permitted provided that the following conditions
// are met:
//
//  * Redistributions of source code must retain the above copyright
//    notice, this list of conditions and the following disclaimer.
//  * Redistributions in binary form must reproduce the above
//    copyright notice, this list of conditions and the following
//    disclaimer in the documentation and/or other materials provided
//    with the distribution.
//  * Neither the name of Open Source Robotics Foundation, Inc. nor the names of its
//    contributors may be used to endorse or promote products derived
//    from this software without specific prior written permission.
//
// THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
// "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
// LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS
// FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE
// COPYRIGHT OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT,
// INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING,
// BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
// LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
// CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
// LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN
// ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
// POSSIBILITY OF SUCH DAMAGE.
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

#ifndef MOVEIT_MOVE_GROUP_INTERFACE__VISIBILITY_CONTROL_H_
#define MOVEIT_MOVE_GROUP_INTERFACE__VISIBILITY_CONTROL_H_

// This logic was borrowed (then namespaced) from the examples on the gcc wiki:
//     https://gcc.gnu.org/wiki/Visibility

#if defined _WIN32 || defined __CYGWIN__
#ifdef __GNUC__
#define MOVEIT_MOVE_GROUP_INTERFACE_EXPORT __attribute__((dllexport))
#define MOVEIT_MOVE_GROUP_INTERFACE_IMPORT __attribute__((dllimport))
#else
#define MOVEIT_MOVE_GROUP_INTERFACE_EXPORT __declspec(dllexport)
#define MOVEIT_MOVE_GROUP_INTERFACE_IMPORT __declspec(dllimport)
#endif
#ifdef MOVEIT_MOVE_GROUP_INTERFACE_BUILDING_DLL
#define MOVEIT_MOVE_GROUP_INTERFACE_PUBLIC MOVEIT_MOVE_GROUP_INTERFACE_EXPORT
#else
#define MOVEIT_MOVE_GROUP_INTERFACE_PUBLIC MOVEIT_MOVE_GROUP_INTERFACE_IMPORT
#endif
#define MOVEIT_MOVE_GROUP_INTERFACE_PUBLIC_TYPE MOVEIT_MOVE_GROUP_INTERFACE_PUBLIC
#define MOVEIT_MOVE_GROUP_INTERFACE_LOCAL
#else
#define MOVEIT_MOVE_GROUP_INTERFACE_EXPORT __attribute__((visibility("default")))
#define MOVEIT_MOVE_GROUP_INTERFACE_IMPORT
#if __GNUC__ >= 4
#define MOVEIT_MOVE_GROUP_INTERFACE_PUBLIC __attribute__((visibility("default")))
#define MOVEIT_MOVE_GROUP_INTERFACE_LOCAL __attribute__((visibility("hidden")))
#else
#define MOVEIT_MOVE_GROUP_INTERFACE_PUBLIC
#define MOVEIT_MOVE_GROUP_INTERFACE_LOCAL
#endif
#define MOVEIT_MOVE_GROUP_INTERFACE_PUBLIC_TYPE
#endif

#endif  // MOVEIT_MOVE_GROUP_INTERFACE__VISIBILITY_CONTROL_H_
