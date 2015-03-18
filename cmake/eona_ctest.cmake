enable_testing()

set(idx 0)
macro (Tester arg result)
    MATH(EXPR idx "${idx} + 1") 
    add_test (${MAIN}${idx} ${MAIN} ${arg})
    set_tests_properties (${MAIN}${idx} 
        PROPERTIES PASS_REGULAR_EXPRESSION ${result})
endmacro()

macro (TesterNoArg result)
    add_test (${MAIN}NoArg ${MAIN} ${arg})
    set_tests_properties (${MAIN}NoArg
        PROPERTIES PASS_REGULAR_EXPRESSION ${result})
endmacro()

# simply check segmentation fault or startup at all
macro (TesterRuns)
    add_test (${MAIN}Runs ${MAIN})
endmacro()

TesterRuns()
TesterNoArg("dudulu 1\nhardware=8")

set(testn 3)
# LESS must be all CAPS!!!
while (testn GREATER 2 AND testn LESS 50)
    MATH(EXPR testn "${testn} * 2") 
    Tester(${testn} "argc ${testn}${testn}")
endwhile()
