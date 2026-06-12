#ifndef __ASM_ARM_COMPILER_H
#define __ASM_ARM_COMPILER_H

/*
 * This is used to ensure the compiler did actually allocate the register we
 * asked it for some inline assembly sequences.  Apparently we can't trust
 * the compiler from one version to another so a bit of paranoia won't hurt.
 * This string is meant to be concatenated with the inline asm string and
 * will cause compilation to stop on mismatch.
 * (for details, see gcc PR 15089)
 * For compatibility with clang, we have to specifically take the equivalence
 * of 'r11' <-> 'fp' and 'r12' <-> 'ip' into account as well.
 *
 * GCC 9+ reliably honors register-constrained asm variables, so the check
 * is a no-op — modern GCC may allocate equivalent but differently-named
 * registers and the .err would fire spuriously.
 */
#if GCC_VERSION < 90000
#define __asmeq(x, y)				\
	".ifnc " x "," y "; "			\
	  ".ifnc " x y ",fpr11; " 		\
	    ".ifnc " x y ",r11fp; "		\
	      ".ifnc " x y ",ipr12; " 		\
	        ".ifnc " x y ",r12ip; "		\
	          ".err; "			\
	        ".endif; "			\
	      ".endif; "			\
	    ".endif; "				\
	  ".endif; "				\
	".endif\n\t"
#else
#define __asmeq(x, y)	""
#endif


#endif /* __ASM_ARM_COMPILER_H */
