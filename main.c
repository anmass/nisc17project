/*
 * NISC Group 17 - Project 2: Traffic lights
 */


#include "ch.h"
#include "hal.h"


// Posizioni Semafori
//______________P1___________________________
//            |____|
//            |____|
//            |____|
//________S1__|____|_________ _______________
//                 | |  |  | |
//                 |_|__|__|_|P2
//                 |         |
//                 |       S2|
//                 |         |
//                 |         |

// Semafori auto
#define S1_GREEN_PORT    GPIOA
#define S1_GREEN_PIN     5U
#define S1_GREEN_LINE    PAL_LINE( S1_GREEN_PORT, S1_GREEN_PIN )
#define S1_RED_PORT      GPIOA
#define S1_RED_PIN       6U
#define S1_RED_LINE      PAL_LINE( S1_BLU_PORT, S1_BLU_PIN )

#define S2_GREEN_PORT    GPIOA
#define S2_GREEN_PIN     7U
#define S2_GREEN_LINE    PAL_LINE( S2_GREEN_PORT, S2_GREEN_PIN )
#define S2_RED_PORT      GPIOB
#define S2_RED_PIN       6U
#define S2_RED_LINE      PAL_LINE( S2_BLU_PORT, S2_BLU_PIN )

// Pedoni (Pin con modalità PWM)
#define P1_GREEN_PORT    GPIOC
#define P1_GREEN_PIN     7U
#define P1_GREEN_LINE    PAL_LINE( P1_GREEN_PORT, P1_GREEN_PIN )
#define P1_RED_PORT      GPIOB
#define P1_RED_PIN       10U
#define P1_RED_LINE      PAL_LINE( P1_BLU_PORT, P1_BLU_PIN )

#define P2_GREEN_PORT    GPIOB
#define P2_GREEN_PIN     4U
#define P2_GREEN_LINE    PAL_LINE( P2_GREEN_PORT, P2_GREEN_PIN )
#define P2_RED_PORT      GPIOB
#define P2_RED_PIN       3U
#define P2_RED_LINE      PAL_LINE( P2_BLU_PORT, P2_BLU_PIN )

// Bottoni
// TODO da definire tutti
#define EXTBTN_PORT     GPIOC
#define EXTBTN_PIN      7U
#define EXTBTN_LINE     PAL_LINE( EXTBTN_PORT, EXTBTN_PIN )




/*
 * Modalità
 */
static uint32_t mode = 0;

/*
 * Working Area and Thread declarations.
 */
static THD_WORKING_AREA( waSem, 128 );
static THD_FUNCTION( thdSem, arg ) {
  (void) arg;

  palSetLineMode( S1_GREEN_LINE, PAL_MODE_OUTPUT_PUSHPULL );
  palSetLineMode( S1_RED_LINE, PAL_MODE_OUTPUT_PUSHPULL );
  palSetLineMode( S2_GREEN_LINE, PAL_MODE_OUTPUT_PUSHPULL );
  palSetLineMode( S2_RED_LINE, PAL_MODE_OUTPUT_PUSHPULL );
  palSetLineMode( P1_GREEN_LINE, PAL_MODE_OUTPUT_PUSHPULL );
  palSetLineMode( P1_RED_LINE, PAL_MODE_OUTPUT_PUSHPULL );
  palSetLineMode( P2_GREEN_LINE, PAL_MODE_OUTPUT_PUSHPULL );
  palSetLineMode( P2_RED_LINE, PAL_MODE_OUTPUT_PUSHPULL );

  while( 1 ) {

    switch(mode) {

       case 0:
         // TODO normal mode
         // TODO forse è meglio un thread separato per ogni semaforo con delle
         // variabili per sincronizzarli

         // S1
         palSetLine(S1_RED_LINE);
         chThdSleepSeconds(1);
         chThdSleepSeconds(9);

         palSetLine(S1_GREEN_LINE);
         palClearLine(S1_RED_LINE);
         chThdSleepSeconds(6);

         palSetLine(S1_GREEN_LINE);
         palSetLine(S1_RED_LINE);
         chThdSleepSeconds(3);

         // S2
         palSetLine(S2_RED_LINE);
         chThdSleepSeconds(1);

         palSetLine(S2_GREEN_LINE);
         palClearLine(S2_RED_LINE);
         chThdSleepSeconds(6);

         palSetLine(S2_GREEN_LINE);
         palSetLine(S2_RED_LINE);
         chThdSleepSeconds(3);

         palClearLine(S2_GREEN_LINE);
         chThdSleepSeconds(9);



          break;

       case 1:
         // TODO night mode
          break;

       case 2:
         //TODO select mode
          break;

       default :
       // normal mode copy
    }
    chThdSleepMilliseconds( 200 );
  }
}



static THD_WORKING_AREA( waOled, 128 );
static THD_FUNCTION( thdOled, arg ) {
  (void) arg;

}



static THD_WORKING_AREA( waButtons, 128 );
static THD_FUNCTION( thdButtons, arg ) {
  (void) arg;

}


static THD_WORKING_AREA( waEncoder, 128 );
static THD_FUNCTION( thdEncoder, arg ) {
  (void) arg;

}



int main(void) {

  halInit();
  chSysInit();

  chThdCreateStatic(waSem, sizeof(waSem), NORMALPRIO+1, thdSem, NULL );
  chThdCreateStatic(waOled, sizeof(waOled), NORMALPRIO+1, thdOled, NULL );
  chThdCreateStatic(waButtons, sizeof(waButtons), NORMALPRIO+1, thdButtons, NULL );
  chThdCreateStatic(waEncoder, sizeof(waEncoder), NORMALPRIO+1, thdEncoder, NULL );

  while (true) {

    // Debouncing o antirimbalzo
    // TODO da spostare
    if( palReadLine( EXTBTN_LINE ) == PAL_LOW ) {
      while( palReadLine( EXTBTN_LINE ) == PAL_LOW ) {
        chThdSleepMilliseconds(20);
      }
    }

    chThdSleepMilliseconds(20);
  }
}
