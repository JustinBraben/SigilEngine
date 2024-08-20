#ifndef SIGIL_ATTRIBUTE_HPP
#define SIGIL_ATTRIBUTE_HPP

#ifndef SIGIL_EXPORT
#    if defined _WIN32 || defined __CYGWIN__ || defined _MSC_VER
#        define SIGIL_EXPORT __declspec(dllexport)
#        define SIGIL_IMPORT __declspec(dllimport)
#        define SIGIL_HIDDEN
#    elif defined __GNUC__ && __GNUC__ >= 4
#        define SIGIL_EXPORT __attribute__((visibility("default")))
#        define SIGIL_IMPORT __attribute__((visibility("default")))
#        define SIGIL_HIDDEN __attribute__((visibility("hidden")))
#    else /* Unsupported compiler */
#        define SIGIL_EXPORT
#        define SIGIL_IMPORT
#        define SIGIL_HIDDEN
#    endif
#endif // SIGIL_EXPORT

#ifndef SIGIL_API
#    if defined SIGIL_API_EXPORT
#        define SIGIL_API SIGIL_EXPORT
#    elif defined SIGIL_API_IMPORT
#        define SIGIL_API SIGIL_IMPORT
#    else /* No API */
#        define SIGIL_API
#    endif
#endif // SIGIL_API

#endif // SIGIL_ATTRIBUTE_HPP