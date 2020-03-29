/*
 *     _   __  _                __ 
 *    / | / / (_)___  _________/ / 
 *   /  |/ / / / __ \/ ___/ __  /  
 *  / /|  / / / /_/ / /  / /_/ /   
 * /_/ |_/_/ /\____/_/   \__,_/    
 *      /___/                      
 *       
 * Author: Lucas Cruz dos Reis(L.C.R.) 
 * Github: https://github.com/LCRERGO 
*/
/* See LICENSE file for copyright and license details. */

#define MAX(A, B)               ((A) > (B) ? (A) : (B))
#define MIN(A, B)               ((A) < (B) ? (A) : (B))
#define BETWEEN(X, A, B)        ((A) <= (X) && (X) <= (B))

void die(const char *fmt, ...);
void *ecalloc(size_t nmemb, size_t size);
