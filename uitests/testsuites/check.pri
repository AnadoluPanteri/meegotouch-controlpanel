QMAKE_EXTRA_TARGETS += check
check.commands=ruby -c $${suites.files} $${cases.files} &&
check.commands+=./$${suites.files}
