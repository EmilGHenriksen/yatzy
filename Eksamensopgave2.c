#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define EYES_ON_DIE 6
#define BONUS_REQ 42
#define BONUS_POINTS 50

/* Prototypes */
int play_yatzy(void);
int upper_section(int number_of_dice);
int lower_section(int number_of_dice);
int *amount_of_num(int *dice, int number_of_dice);
int *roll_dice(int number_of_dice);
int dice_value(void);
int one_pair(int number_of_dice);
int two_pair(int number_of_dice);
int three_of_a_kind(int number_of_dice);
int four_of_a_kind(int number_of_dice);
int small_straight(int number_of_dice);
int large_straight(int number_of_dice);
int full_house(int number_of_dice);
int chance(int number_of_dice);
int yatzy(int number_of_dice);

int main (void) {
    srand(time(NULL));
    play_yatzy();
    return 0;
}

int play_yatzy(void) {
    int number_of_dice = 0,
        true = 1,
        scanres = 0;

/*
 * Here the input is dertimed, as the number of dice, and the two main functions of the yatzy game a called those being upper_section and lower_section
 * The total score is equal to the total score from the upper_section added to the total score from the lower_section
 */
    do {
        printf("Enter amount of dice, you want to play with (Under 5 terminates): \n");
        scanres = scanf(" %d", &number_of_dice);
        if (scanres != 1) {
            fflush(stdin);
            printf("Invalid input, try again\n");
        }
        else if (number_of_dice >= 5) {
            printf("Total score = %d\n", upper_section(number_of_dice) + lower_section(number_of_dice));
        }
        else if (number_of_dice < 5) {
            true = 0;
        }
    } while(true);
    return 0;
}

/*
 * upper_section calculates the amount of dice that are of the value 1, 2, 3, 4 ,5 & 6 and adds them together
 * if the sum of all the numbers is over 42 then the user will get 50 bonus points
 * at last the total of every numbers sum and the bonus is returned
 */
int upper_section(int number_of_dice) {
    int round = 0,
        *ptr,
        *amount,
        bonus = 0,
        sum_of_num[EYES_ON_DIE] = {0, 0, 0, 0, 0, 0};

        for (round = 0; round < EYES_ON_DIE; round++) {
            ptr = roll_dice(number_of_dice);
            amount = amount_of_num(ptr, number_of_dice);
            if (*(amount + round) > 5) {
                sum_of_num[round] = (round + 1) * 5;
            }
            else if (*(amount + round) <= 5) {
                sum_of_num[round] = (*(amount + round)) * (round + 1);
            }
            printf("Sum of %ds = %d\n\n", round+1, sum_of_num[round]);
        }
        if ((sum_of_num[0] + sum_of_num[1] + sum_of_num[2] + sum_of_num[3] + sum_of_num[4] + sum_of_num[5]) >= BONUS_REQ) {
            bonus = BONUS_POINTS;
        }
        printf("Bonus = %d\n\n", bonus);

    free(ptr);
    return sum_of_num[0] + sum_of_num[1] + sum_of_num[2] + sum_of_num[3] + sum_of_num[4] + sum_of_num[5] + bonus;
}

/* lower_section calls every function that is relevant to the lower_section and add the total score of them all then returns it*/
int lower_section(int number_of_dice) {
    int total = 0,
        score = 0;

    printf("One Pair = %d\n\n", score = one_pair(number_of_dice));
    total += score;

    printf("Two Pair = %d\n\n", score = two_pair(number_of_dice));
    total += score;

    printf("Three of a kind = %d\n\n", score = three_of_a_kind(number_of_dice));
    total += score;

    printf("Four of a kind = %d\n\n", score = four_of_a_kind(number_of_dice));
    total += score;

    printf("Small straight = %d\n\n", score = small_straight(number_of_dice));
    total += score;

    printf("Large straight = %d\n\n", score = large_straight(number_of_dice));
    total += score;

    printf("Full House = %d\n\n", score = full_house(number_of_dice));
    total += score;

    printf("Chance = %d\n\n", score = chance(number_of_dice));
    total += score;

    printf("Yatzy = %d\n\n", score = yatzy(number_of_dice));
    total += score;

    return total;
}

/*
 * amount_of_num finds the amount of each number (1-6) from the input pointer's array
 * The difference between amount_of_num and number_of_dice is that number_of_dice is how many dice in total is used
 * and amount_of_num is how many of each number (1-6) there is amongst the given number_of_dice
*/
int *amount_of_num(int *dice, int number_of_dice) {
    int i = 0,
        j = 0;
    static int amount_of_dice[EYES_ON_DIE] = {0, 0, 0, 0, 0, 0};

    for (j = 0; j < EYES_ON_DIE; j++) {
        amount_of_dice[j] = 0;
    }

    for (i = 0; i < number_of_dice; i++) {
        if (*(dice + i) == 1) {
            amount_of_dice[0] += 1;
        }
        else if (*(dice + i) == 2) {
            amount_of_dice[1] += 1;
        }
        else if (*(dice + i) == 3) {
            amount_of_dice[2] += 1;
        }
        else if (*(dice + i) == 4) {
            amount_of_dice[3] += 1;
        }
        else if (*(dice + i) == 5) {
            amount_of_dice[4] += 1;
        }
        else if (*(dice + i) == 6) {
            amount_of_dice[5] += 1;
        }
    }
    return amount_of_dice;
}

/*
 * roll_dice will take the number_of_dice as an input and allocate memeory in the heap for the given number of dice.
 * The memory will then be filled with random numbers from 1-6
 * roll_dice will then return a pointer to the allocated memory
 */
int *roll_dice(int number_of_dice) {
    int i = 0,
        *dice = (int *) malloc((number_of_dice) * (sizeof(int)));;

    if (dice == NULL) {
            printf("Error! memory not allocated.");
            exit(0);
    }

    for (i = 0; i < number_of_dice; i++) {
        *(dice + i) = dice_value();
         printf("%d ", *(dice + i));
    }
    printf("\n");
    return dice;
}

/* dice_value simply generates a random number between 1-6 and then returns it */
int dice_value(void) {
    return (rand() % EYES_ON_DIE + 1);
}

/* one_pair will take the number of dice as an input and output the sum of the highest pair from the memory given by dice */
int one_pair(int number_of_dice) {
    int *dice = roll_dice(number_of_dice),
        *amount = amount_of_num(dice, number_of_dice),
        sum_of_first_pair = 0,
        i = 0;

/* When looping through the amount of each number, it will assign the last possible pair to sum_of_first_pair */
    for (i = 0; i < 6; i++) {
        if (*(amount + i) >= 2) {
            sum_of_first_pair = ((i + 1) * 2);
        }
    }
    free(dice);
    return sum_of_first_pair;
}

/* two_pair will take the number of dice as an input and output the sum of the two highest pairs from the memory given by dice  */
int two_pair(int number_of_dice) {
    int *dice = roll_dice(number_of_dice),
        *amount = amount_of_num(dice, number_of_dice),
        *check_for_same_num = NULL,
        check_for_pair = 0,
        check_for_second_pair = 0,
        sum_of_first_pair = 0,
        sum_of_second_pair = 0,
        i = 0;

/* If there is one pair it will set the adress of that number to check_for_same_nu, so that it won't pick the same pair twice */
    for (i = 0; i < 6; i++) {
        if (*(amount + i) >= 2) {
            sum_of_first_pair = ((i + 1) * 2);
            check_for_same_num = (amount + i);
            check_for_pair = 1;
        }
    }
    for (i = 0; i < 6; i++) {
        if (*(amount + i) >= 2 && (amount + i) != check_for_same_num && check_for_pair == 1) {
            sum_of_second_pair = ((i + 1) * 2);
            check_for_second_pair = 1;
        }
    }
/* if there are no pairs, it will return 0 */
    if (check_for_pair == 0 || check_for_second_pair == 0) {
        sum_of_first_pair = 0;
        sum_of_second_pair = 0;
    }
    free(dice);
    return (sum_of_first_pair + sum_of_second_pair);
}

/* three_of_a_kind will take the number of dice as an input and output the sum of the highest three of a kind from the memory given by dice */
int three_of_a_kind(int number_of_dice) {
    int *dice = roll_dice(number_of_dice),
        *amount = amount_of_num(dice, number_of_dice),
        sum_three_of_a_kind = 0,
        i = 0;

    for (i = 0; i < 6; i++) {
        if (*(amount + i) >= 3) {
            sum_three_of_a_kind = ((i + 1) * 3);
        }
    }
    free(dice);
    return sum_three_of_a_kind;
}

/* four_of_a_kind will take the number of dice as an input and output the sum of the highest four of a kind from the memory given by dice */
int four_of_a_kind(int number_of_dice) {
    int *dice = roll_dice(number_of_dice),
        *amount = amount_of_num(dice, number_of_dice),
        sum_four_of_a_kind = 0,
        i = 0;

    for (i = 0; i < 6; i++) {
        if (*(amount + i) >= 4) {
            sum_four_of_a_kind = ((i + 1) * 4);
        }
    }
    free(dice);
    return sum_four_of_a_kind;
}

/* small_straight will take the number of dice as an input and output 15 if the amount of 1s, 2s, 3s, 4s, & 5s is greater than 1*/
int small_straight(int number_of_dice) {
    int *dice = roll_dice(number_of_dice),
        *amount = amount_of_num(dice, number_of_dice),
        small_straight = 0;

    if (*(amount) >= 1 && *(amount + 1) >= 1 && *(amount + 2) >= 1 && *(amount + 3) >= 1 && *(amount + 4) >= 1) {
        small_straight = 15;
    }
    free(dice);
    return small_straight;
}

/* large_straight will take the number of dice as an input and output 20 if the amount of 2s, 3s, 4s, 5s, & 6s is greater than 1*/
int large_straight(int number_of_dice) {
    int *dice = roll_dice(number_of_dice),
        *amount = amount_of_num(dice, number_of_dice),
        large_straight = 0;

    if (*(amount + 1) >= 1 && *(amount + 2) >= 1 && *(amount + 3) >= 1 && *(amount + 4) >= 1 && *(amount + 5) >= 1) {
        large_straight = 20;
    }
    free(dice);
    return large_straight;
}

/* full_house will check for highest three of a kind, if there is three of a kind then it will find the highest pair, that is not the three_of_a_kind */
int full_house(int number_of_dice) {
    int *dice = roll_dice(number_of_dice),
        *amount = amount_of_num(dice, number_of_dice),
        sum_three_of_a_kind = 0,
        sum_of_second_pair = 0,
        check_for_pair = 0,
        *check_for_same_num = 0,
        check_for_full_house = 0,
        i = 0;

/* Finds highest three of a kind */
    for (i = 0; i < 6; i++) {
        if (*(amount + i) >= 3) {
            sum_three_of_a_kind = ((i + 1) * 3);
            check_for_same_num = (amount + i);
            check_for_full_house = 1;
        }
    }
    for (i = 0; i < 6; i++) {
        if (*(amount + i) >= 2 && (amount + i) != check_for_same_num && check_for_full_house == 1) {
            sum_of_second_pair = ((i + 1) * 2);
            check_for_pair = 1;
        }
    }
/* if there is no pair, or three of a kind it will return 0 */
    if (check_for_full_house == 0 || check_for_pair == 0) {
        sum_three_of_a_kind = 0;
        sum_of_second_pair = 0;
    }
    free(dice);
    return (sum_three_of_a_kind + sum_of_second_pair);
}

/* chance will find the 5 largest dice and add them together */
int chance(int number_of_dice) {
    int *dice = roll_dice(number_of_dice),
        *amount = amount_of_num(dice, number_of_dice),
        check = 0,
        chance = 0,
        i = 0;

/*
 * The function loops from 6 - 1 and adds the amount of that die times itself to the varialbe chance
 * it then adds the amount of that die to the variable check.
 * If check gets above 5, it will subtract the amount its gone over from chance, and stop adding to chance
*/
    for (i = 5; i > -1; i--) {
        if (*(amount + i) >= 1 && check <= 5 && *(amount + i) <= 5) {
            chance += (i + 1) * (*(amount + i));
            check += *(amount + i);
            if (check > 5) {
                chance -= (check - 5) * (i + 1);
            }
        }
        else if (*(amount + i) > 5 && chance == 0) {
            chance += (i + 1) * 5;
            check = 5;
        }
    }
    free(dice);
    return chance;
}

/* yatzy (five of a kind) will take the number of dice as an input and output the sum of the highest five of a kind from the memory given by dice  */
int yatzy(int number_of_dice) {
    int *dice = roll_dice(number_of_dice),
        *amount = amount_of_num(dice, number_of_dice),
        yatzy = 0,
        i = 0;

    for (i = 0; i < 6; i++) {
        if (*(amount + i) >= 5) {
            yatzy = ((i + 1) * 5);
        }
    }
    free(dice);
    return yatzy;
}
