# Install script for directory: E:/Faculty-Content/2nd Semester/Structured Programming 1/Assighnments/Assignment 4/Programming_Assignment_4/Login_Application/OpenXLSX/OpenXLSX

# Set the install prefix
if(NOT DEFINED CMAKE_INSTALL_PREFIX)
  set(CMAKE_INSTALL_PREFIX "C:/Program Files (x86)/Login_Application")
endif()
string(REGEX REPLACE "/$" "" CMAKE_INSTALL_PREFIX "${CMAKE_INSTALL_PREFIX}")

# Set the install configuration name.
if(NOT DEFINED CMAKE_INSTALL_CONFIG_NAME)
  if(BUILD_TYPE)
    string(REGEX REPLACE "^[^A-Za-z0-9_]+" ""
           CMAKE_INSTALL_CONFIG_NAME "${BUILD_TYPE}")
  else()
    set(CMAKE_INSTALL_CONFIG_NAME "Debug")
  endif()
  message(STATUS "Install configuration: \"${CMAKE_INSTALL_CONFIG_NAME}\"")
endif()

# Set the component getting installed.
if(NOT CMAKE_INSTALL_COMPONENT)
  if(COMPONENT)
    message(STATUS "Install component: \"${COMPONENT}\"")
    set(CMAKE_INSTALL_COMPONENT "${COMPONENT}")
  else()
    set(CMAKE_INSTALL_COMPONENT)
  endif()
endif()

# Is this installation the result of a crosscompile?
if(NOT DEFINED CMAKE_CROSSCOMPILING)
  set(CMAKE_CROSSCOMPILING "FALSE")
endif()

# Set default install directory permissions.
if(NOT DEFINED CMAKE_OBJDUMP)
  set(CMAKE_OBJDUMP "C:/MinGW/bin/objdump.exe")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/OpenXLSX/headers" TYPE FILE FILES "E:/Faculty-Content/2nd Semester/Structured Programming 1/Assighnments/Assignment 4/Programming_Assignment_4/Login_Application/build/OpenXLSX/OpenXLSX/OpenXLSX-Exports.hpp")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/OpenXLSX/headers" TYPE FILE FILES
    "E:/Faculty-Content/2nd Semester/Structured Programming 1/Assighnments/Assignment 4/Programming_Assignment_4/Login_Application/OpenXLSX/OpenXLSX/headers/XLCell.hpp"
    "E:/Faculty-Content/2nd Semester/Structured Programming 1/Assighnments/Assignment 4/Programming_Assignment_4/Login_Application/OpenXLSX/OpenXLSX/headers/XLCellIterator.hpp"
    "E:/Faculty-Content/2nd Semester/Structured Programming 1/Assighnments/Assignment 4/Programming_Assignment_4/Login_Application/OpenXLSX/OpenXLSX/headers/XLCellRange.hpp"
    "E:/Faculty-Content/2nd Semester/Structured Programming 1/Assighnments/Assignment 4/Programming_Assignment_4/Login_Application/OpenXLSX/OpenXLSX/headers/XLCellReference.hpp"
    "E:/Faculty-Content/2nd Semester/Structured Programming 1/Assighnments/Assignment 4/Programming_Assignment_4/Login_Application/OpenXLSX/OpenXLSX/headers/XLCellValue.hpp"
    "E:/Faculty-Content/2nd Semester/Structured Programming 1/Assighnments/Assignment 4/Programming_Assignment_4/Login_Application/OpenXLSX/OpenXLSX/headers/XLColor.hpp"
    "E:/Faculty-Content/2nd Semester/Structured Programming 1/Assighnments/Assignment 4/Programming_Assignment_4/Login_Application/OpenXLSX/OpenXLSX/headers/XLColumn.hpp"
    "E:/Faculty-Content/2nd Semester/Structured Programming 1/Assighnments/Assignment 4/Programming_Assignment_4/Login_Application/OpenXLSX/OpenXLSX/headers/XLCommandQuery.hpp"
    "E:/Faculty-Content/2nd Semester/Structured Programming 1/Assighnments/Assignment 4/Programming_Assignment_4/Login_Application/OpenXLSX/OpenXLSX/headers/XLConstants.hpp"
    "E:/Faculty-Content/2nd Semester/Structured Programming 1/Assighnments/Assignment 4/Programming_Assignment_4/Login_Application/OpenXLSX/OpenXLSX/headers/XLContentTypes.hpp"
    "E:/Faculty-Content/2nd Semester/Structured Programming 1/Assighnments/Assignment 4/Programming_Assignment_4/Login_Application/OpenXLSX/OpenXLSX/headers/XLDateTime.hpp"
    "E:/Faculty-Content/2nd Semester/Structured Programming 1/Assighnments/Assignment 4/Programming_Assignment_4/Login_Application/OpenXLSX/OpenXLSX/headers/XLDocument.hpp"
    "E:/Faculty-Content/2nd Semester/Structured Programming 1/Assighnments/Assignment 4/Programming_Assignment_4/Login_Application/OpenXLSX/OpenXLSX/headers/XLException.hpp"
    "E:/Faculty-Content/2nd Semester/Structured Programming 1/Assighnments/Assignment 4/Programming_Assignment_4/Login_Application/OpenXLSX/OpenXLSX/headers/XLFormula.hpp"
    "E:/Faculty-Content/2nd Semester/Structured Programming 1/Assighnments/Assignment 4/Programming_Assignment_4/Login_Application/OpenXLSX/OpenXLSX/headers/XLIterator.hpp"
    "E:/Faculty-Content/2nd Semester/Structured Programming 1/Assighnments/Assignment 4/Programming_Assignment_4/Login_Application/OpenXLSX/OpenXLSX/headers/XLProperties.hpp"
    "E:/Faculty-Content/2nd Semester/Structured Programming 1/Assighnments/Assignment 4/Programming_Assignment_4/Login_Application/OpenXLSX/OpenXLSX/headers/XLRelationships.hpp"
    "E:/Faculty-Content/2nd Semester/Structured Programming 1/Assighnments/Assignment 4/Programming_Assignment_4/Login_Application/OpenXLSX/OpenXLSX/headers/XLRow.hpp"
    "E:/Faculty-Content/2nd Semester/Structured Programming 1/Assighnments/Assignment 4/Programming_Assignment_4/Login_Application/OpenXLSX/OpenXLSX/headers/XLRowData.hpp"
    "E:/Faculty-Content/2nd Semester/Structured Programming 1/Assighnments/Assignment 4/Programming_Assignment_4/Login_Application/OpenXLSX/OpenXLSX/headers/XLSharedStrings.hpp"
    "E:/Faculty-Content/2nd Semester/Structured Programming 1/Assighnments/Assignment 4/Programming_Assignment_4/Login_Application/OpenXLSX/OpenXLSX/headers/XLSheet.hpp"
    "E:/Faculty-Content/2nd Semester/Structured Programming 1/Assighnments/Assignment 4/Programming_Assignment_4/Login_Application/OpenXLSX/OpenXLSX/headers/XLWorkbook.hpp"
    "E:/Faculty-Content/2nd Semester/Structured Programming 1/Assighnments/Assignment 4/Programming_Assignment_4/Login_Application/OpenXLSX/OpenXLSX/headers/XLXmlData.hpp"
    "E:/Faculty-Content/2nd Semester/Structured Programming 1/Assighnments/Assignment 4/Programming_Assignment_4/Login_Application/OpenXLSX/OpenXLSX/headers/XLXmlFile.hpp"
    "E:/Faculty-Content/2nd Semester/Structured Programming 1/Assighnments/Assignment 4/Programming_Assignment_4/Login_Application/OpenXLSX/OpenXLSX/headers/XLXmlParser.hpp"
    "E:/Faculty-Content/2nd Semester/Structured Programming 1/Assighnments/Assignment 4/Programming_Assignment_4/Login_Application/OpenXLSX/OpenXLSX/headers/XLZipArchive.hpp"
    )
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/OpenXLSX" TYPE FILE FILES "E:/Faculty-Content/2nd Semester/Structured Programming 1/Assighnments/Assignment 4/Programming_Assignment_4/Login_Application/OpenXLSX/OpenXLSX/OpenXLSX.hpp")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xlibx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib" TYPE STATIC_LIBRARY FILES "E:/Faculty-Content/2nd Semester/Structured Programming 1/Assighnments/Assignment 4/Programming_Assignment_4/Login_Application/build/output/libOpenXLSXd.a")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib/cmake/OpenXLSX" TYPE FILE FILES
    "E:/Faculty-Content/2nd Semester/Structured Programming 1/Assighnments/Assignment 4/Programming_Assignment_4/Login_Application/OpenXLSX/OpenXLSX/OpenXLSXConfig.cmake"
    "E:/Faculty-Content/2nd Semester/Structured Programming 1/Assighnments/Assignment 4/Programming_Assignment_4/Login_Application/build/OpenXLSX/OpenXLSX/OpenXLSX/OpenXLSXConfigVersion.cmake"
    )
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  if(EXISTS "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/cmake/OpenXLSX/OpenXLSXTargets.cmake")
    file(DIFFERENT EXPORT_FILE_CHANGED FILES
         "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/cmake/OpenXLSX/OpenXLSXTargets.cmake"
         "E:/Faculty-Content/2nd Semester/Structured Programming 1/Assighnments/Assignment 4/Programming_Assignment_4/Login_Application/build/OpenXLSX/OpenXLSX/CMakeFiles/Export/lib/cmake/OpenXLSX/OpenXLSXTargets.cmake")
    if(EXPORT_FILE_CHANGED)
      file(GLOB OLD_CONFIG_FILES "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/cmake/OpenXLSX/OpenXLSXTargets-*.cmake")
      if(OLD_CONFIG_FILES)
        message(STATUS "Old export file \"$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/cmake/OpenXLSX/OpenXLSXTargets.cmake\" will be replaced.  Removing files [${OLD_CONFIG_FILES}].")
        file(REMOVE ${OLD_CONFIG_FILES})
      endif()
    endif()
  endif()
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib/cmake/OpenXLSX" TYPE FILE FILES "E:/Faculty-Content/2nd Semester/Structured Programming 1/Assighnments/Assignment 4/Programming_Assignment_4/Login_Application/build/OpenXLSX/OpenXLSX/CMakeFiles/Export/lib/cmake/OpenXLSX/OpenXLSXTargets.cmake")
  if("${CMAKE_INSTALL_CONFIG_NAME}" MATCHES "^([Dd][Ee][Bb][Uu][Gg])$")
    file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib/cmake/OpenXLSX" TYPE FILE FILES "E:/Faculty-Content/2nd Semester/Structured Programming 1/Assighnments/Assignment 4/Programming_Assignment_4/Login_Application/build/OpenXLSX/OpenXLSX/CMakeFiles/Export/lib/cmake/OpenXLSX/OpenXLSXTargets-debug.cmake")
  endif()
endif()

