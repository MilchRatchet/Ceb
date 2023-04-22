#
# Copyright (c) 2023, MilchRatchet
#
# Permission is hereby granted, free of charge, to any person obtaining a copy
# of this software and associated documentation files (the "Software"), to deal
# in the Software without restriction, including without limitation the rights
# to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
# copies of the Software, and to permit persons to whom the Software is
# furnished to do so, subject to the following conditions:
#
# The above copyright notice and this permission notice shall be included in all
# copies or substantial portions of the Software.
#
# THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
# IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
# FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
# AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
# LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
# OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
# SOFTWARE.
#
function(ceb_embed_files)
  set(options)
  set(oneValueArgs PROJECT OUTPUT)
  set(multiValueArgs INPUT)
  cmake_parse_arguments(EMBED_FILES "${options}" "${oneValueArgs}" "${multiValueArgs}" ${ARGN})
  set(EMBED_FILES_CEB_EXECUTABLE "$<TARGET_FILE:Ceb>")
  add_custom_command(
    OUTPUT ${EMBED_FILES_OUTPUT}.c
    COMMAND ${EMBED_FILES_CEB_EXECUTABLE} ${EMBED_FILES_OUTPUT} ${EMBED_FILES_INPUT}
    WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
    DEPENDS ${EMBED_FILES_INPUT} Ceb)
  set(CEB_OUTPUT_FILE_${EMBED_FILES_OUTPUT} ${CMAKE_CURRENT_BINARY_DIR}/${EMBED_FILES_OUTPUT}.c)
  return(PROPAGATE CEB_OUTPUT_FILE_${EMBED_FILES_OUTPUT})
endfunction()
