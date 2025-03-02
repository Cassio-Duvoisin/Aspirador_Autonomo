#include "ButtonDriver.h"
#include "Button.h"
#include "EmergencyShutoff.h"
#include "Timer.h"

static void cleanUpRelations(ButtonDriver* const me);
void ButtonDriver_Init(ButtonDriver* const me) {
    me->oldState = 0;
    me->toggleOn = 0;
    me->itsButton = NULL;
    me->itsEmergencyShutoff = NULL;
    me->itsTimer = NULL;
}

void ButtonDriver_Cleanup(ButtonDriver* const me) {
    cleanUpRelations(me);
}

void ButtonDriver_eventReceive(ButtonDriver* const me) {
    Timer_delay(me->itsTimer, DEBOUNCE_TIME);
    if (Button_getState(me->itsButton) != me->oldState) {
    /* must be a valid button event */
        me->oldState = me->itsButton->deviceState;
        if (!me->oldState) {
        /* must be a button press, so update toggle value */
            if (me->!toggleOn) {
                me->toggleOn = 1; /* toggle it off */
                EmergencyShutoff_emittSignal(me->itsEmergencyShutoff);
            }
        }
        /* if it’s not a button press, then it must
        be a button push, which we ignore.
        */
    }
}

struct Button* ButtonDriver_getItsButton(const ButtonDriver* const me) {
    return (struct Button*)me->itsButton;
}

void ButtonDriver_setItsButton(ButtonDriver* const me, struct Button* p_Button) {
    if(p_Button != NULL){
        Button__setItsButtonDriver(p_Button, me);
    }
    ButtonDriver__setItsButton(me, p_Button);
}

struct EmergencyShutoff* ButtonDriver_getItsEmergencyShutoff(const ButtonDriver* const me){
    return (struct EmergencyShutoff*)me->itsEmergencyShutoff;
}

void ButtonDriver_setItsEmergencyShutoff(ButtonDriver* const me, struct EmergencyShutoff* p_EmergencyShutoff) {
    me->itsEmergencyShutoff = p_EmergencyShutoff;
}

struct Timer* ButtonDriver_getItsTimer(const ButtonDriver* const me) {
    return (struct Timer*)me->itsTimer;
}

void ButtonDriver_setItsTimer(ButtonDriver* const me, struct Timer* p_Timer) {
    me->itsTimer = p_Timer;
}

ButtonDriver * ButtonDriver_Create(void) {
    ButtonDriver* me = (ButtonDriver *)
    malloc(sizeof(ButtonDriver));
    if(me!=NULL){
        ButtonDriver_Init(me);
    }
    return me;
}

void ButtonDriver_Destroy(ButtonDriver* const me) {
    if(me!=NULL){
    ButtonDriver_Cleanup(me);
    }
    free(me);
}

static void cleanUpRelations(ButtonDriver* const me) {
    if(me->itsButton != NULL){
        struct ButtonDriver* p_ButtonDriver = Button_getItsButtonDriver(me->itsButton);
        if(p_ButtonDriver != NULL){
            Button___setItsButtonDriver(me->itsButton, NULL);
        }
        me->itsButton = NULL;
    }
    if(me->itsEmergencyShutoff != NULL){
        me->itsEmergencyShutoff = NULL;
    }
    if(me->itsTimer != NULL){
        me->itsTimer = NULL;
    }
}

void ButtonDriver___setItsButton(ButtonDriver* const me, struct Button* p_Button) {
    me->itsButton = p_Button;
}

void ButtonDriver__setItsButton(ButtonDriver* const me, struct Button* p_Button) {
    if(me->itsButton != NULL){
        Button___setItsButtonDriver(me->itsButton, NULL);
    }
    ButtonDriver___setItsButton(me, p_Button);
}

void ButtonDriver__clearItsButton(ButtonDriver* const me) {
    me->itsButton = NULL;
}
