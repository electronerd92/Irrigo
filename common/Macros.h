#ifndef MACROS_H
#define MACROS_H

// Character extraction macros
#define CHAR_0(s) s[0]
#define CHAR_1(s) s[1]
#define CHAR_2(s) s[2]
#define CHAR_3(s) s[3]
#define CHAR_4(s) s[4]
#define CHAR_5(s) s[5]
#define CHAR_6(s) s[6]
#define CHAR_7(s) s[7]
#define CHAR_8(s) s[8]
#define CHAR_9(s) s[9]

// Reversal macros
#define REVERSE_1(a) a
#define REVERSE_2(a, b) b, a
#define REVERSE_3(a, b, c) c, b, a
#define REVERSE_4(a, b, c, d) d, c, b, a
#define REVERSE_5(a, b, c, d, e) e, d, c, b, a
#define REVERSE_6(a, b, c, d, e, f) f, e, d, c, b, a
#define REVERSE_7(a, b, c, d, e, f, g) g, f, e, d, c, b, a
#define REVERSE_8(a, b, c, d, e, f, g, h) h, g, f, e, d, c, b, a
#define REVERSE_9(a, b, c, d, e, f, g, h, i) i, h, g, f, e, d, c, b, a
#define REVERSE_10(a, b, c, d, e, f, g, h, i, j) j, i, h, g, f, e, d, c, b, a

// Helper macro to reverse a string literal of a specific length
#define REVERSE_STRING_1(s) REVERSE_1(CHAR_0(s))
#define REVERSE_STRING_2(s) REVERSE_2(CHAR_0(s), CHAR_1(s))
#define REVERSE_STRING_3(s) REVERSE_3(CHAR_0(s), CHAR_1(s), CHAR_2(s))
#define REVERSE_STRING_4(s) REVERSE_4(CHAR_0(s), CHAR_1(s), CHAR_2(s), CHAR_3(s))
#define REVERSE_STRING_5(s) REVERSE_5(CHAR_0(s), CHAR_1(s), CHAR_2(s), CHAR_3(s), CHAR_4(s))
#define REVERSE_STRING_6(s) REVERSE_6(CHAR_0(s), CHAR_1(s), CHAR_2(s), CHAR_3(s), CHAR_4(s), CHAR_5(s))
#define REVERSE_STRING_7(s) REVERSE_7(CHAR_0(s), CHAR_1(s), CHAR_2(s), CHAR_3(s), CHAR_4(s), CHAR_5(s), CHAR_6(s))
#define REVERSE_STRING_8(s) REVERSE_8(CHAR_0(s), CHAR_1(s), CHAR_2(s), CHAR_3(s), CHAR_4(s), CHAR_5(s), CHAR_6(s), CHAR_7(s))
#define REVERSE_STRING_9(s) REVERSE_9(CHAR_0(s), CHAR_1(s), CHAR_2(s), CHAR_3(s), CHAR_4(s), CHAR_5(s), CHAR_6(s), CHAR_7(s), CHAR_8(s))
#define REVERSE_STRING_10(s) REVERSE_10(CHAR_0(s), CHAR_1(s), CHAR_2(s), CHAR_3(s), CHAR_4(s), CHAR_5(s), CHAR_6(s), CHAR_7(s), CHAR_8(s), CHAR_9(s))

// Select appropriate reversal macro based on length
#define REVERSE_SELECT(N) REVERSE_STRING_##N

// Define a macro to return a string literal
#define MAKE_STRING_LITERAL(...) #__VA_ARGS__

// Main reversal macro
#define REVERSE_STRING(s, N) MAKE_STRING_LITERAL(REVERSE_SELECT(N)(s))

//// Main reversal macro
// #def ine REVERSE_STRIN G(s, N)           \
//    (const char[]) { REVERSE_SELECT(N) \
//                     (s), '\0' }
//
#endif // MACROS_H