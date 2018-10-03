/*
 * debug.h
 *
 *  Created on: Oct 3, 2018
 *      Author: user
 */

#ifndef LIB_DEBUG_H_
#define LIB_DEBUG_H_

#if DEBUG == 0
#define assert(s)
#elif DEBUG == 1
#define assert(s) fprintf(stderr, "%s\n", s)
#endif



#endif /* LIB_DEBUG_H_ */
