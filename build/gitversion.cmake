# Write the source commit the compiler is built from into a generated header,
# so that a binary can be traced back to its source. Run in script mode at
# BUILD time, not at configure time, so the value does not go stale after a
# commit. Expects SRC (the repository) and OUT (the header to write).
#
# The header is rewritten only when its content changes, so a build that does
# not move the commit does not recompile what includes it.

set (COMMIT "unknown")

find_package (Git QUIET)
if (GIT_FOUND AND EXISTS "${SRC}/.git")
    execute_process (
        COMMAND "${GIT_EXECUTABLE}" rev-parse --short=9 HEAD
        WORKING_DIRECTORY "${SRC}"
        OUTPUT_VARIABLE SHA OUTPUT_STRIP_TRAILING_WHITESPACE
        ERROR_QUIET RESULT_VARIABLE STATUS)
    if (STATUS EQUAL 0 AND SHA)
        set (COMMIT "${SHA}")
        # A binary built from a modified tree is not the commit it names, and a
        # gate that reports the commit alone would be reporting a fiction.
        execute_process (
            COMMAND "${GIT_EXECUTABLE}" status --porcelain --untracked-files=no
            WORKING_DIRECTORY "${SRC}"
            OUTPUT_VARIABLE DIRTY OUTPUT_STRIP_TRAILING_WHITESPACE
            ERROR_QUIET RESULT_VARIABLE DSTATUS)
        if (DSTATUS EQUAL 0 AND NOT DIRTY STREQUAL "")
            set (COMMIT "${SHA}-modified")
        endif()
    endif()
endif()

set (CONTENT "// Generated at build time by build/gitversion.cmake -- do not edit.\n#define FAUSTGITVERSION \"${COMMIT}\"\n")

set (PREVIOUS "")
if (EXISTS "${OUT}")
    file (READ "${OUT}" PREVIOUS)
endif()
if (NOT PREVIOUS STREQUAL CONTENT)
    file (WRITE "${OUT}" "${CONTENT}")
endif()
