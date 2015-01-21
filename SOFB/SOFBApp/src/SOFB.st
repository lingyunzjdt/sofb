/* Sequencer to control the on-demond record process: ramping table download, power supply mode change, and watch funciton upload */

#define PRINTF seqLog

program sofbST

/* options */
option  +r;
option  -c; 

char ORMStart;
assign ORMStart to "{ORMStart}";
monitor ORMStart;

char ORM1stKick;
assign ORM1stKick to "{ORM1stKick}";
monitor ORM1stKick;

ss ORM {
	state ORM_Idle {
		when(ORMStart==1) {
			ORM1stKick=1;
			pvPut(ORM1stKick);
		} state ORM_Delay1		
		when (delay(1)) {
		} state ORM_Delay2
	}
	state ORM_Delay1 {
		when (delay(4)) {
		} state ORM_Idle
	}	
	state ORM_Delay2 {
		when (delay(1)) {
		} state ORM_Idle
	}	
}


