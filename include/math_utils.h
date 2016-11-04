#ifndef __MATH_UTILS_H__
#define __MATH_UTILS_H__

#ifndef max
#define max(a,b) ((a) > (b) ? (a) : (b))
#endif
/*
 * @author : Nicolas
 * @date   : 28 / 10 / 2016
 * @state  : [No bug]
 * 
 * @name   : init_seed_to_null
 * @desc   : This function is used to init random seed to null
 *
 * @return : Pointer on generated linked list element;
 */
void init_seed_to_null();


/*
 * @author : Nicolas
 * @date   : 28 / 10 / 2016
 * @state  : [No bug]
 * 
 * @name   : random_int
 * @arg    : min , min value range for random generation
 * @arg    : max , max value range for random generation
 * @desc   : This function is used to generate random integer value between min and max
 *
 * @return : return random int value generated;
 */
int random_int(int min, int max);


/*
 * @author : Nicolas
 * @date   : 28 / 10 / 2016
 * @state  : [No bug]
 * 
 * @name   : random_double
 * @arg    : min , min value range for random generation
 * @arg    : max , max value range for random generation
 * @desc   : This function is used to generate random integer value between min and max
 *
 * @return : return random double value generated;
 */
double random_double(double min,double max);

/*
 * @author : Nicolas
 * @date   : 02 / 11 / 2016
 * @state  : [No bug]
 * 
 * @name   : random_double_in_poke_range
 * @desc   : This function is used to generate random integer value between random generation
             use in all poke system that mean 0.9, 1.0 or 1.1
 *
 * @return : return random double value generated;
 */
double random_double_in_poke_range();

#endif
