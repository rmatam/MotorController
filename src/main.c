#include "ch.h"
#include "hal.h"
#include "imudriver.h"
#include "tr_types.h"
#include "position.h"
#include "orientation.h"
#include "test_position.h"
#include "test_orientation.h"
#include "test.h"
#include "i2c_interface.h"
#include "coding_wheels.h"
#include "motor.h"
#include "RTT/SEGGER_RTT.h"
#include "control.h"
#include "settings.h"

int main(void) {
	// initialize ChibiOS
	halInit();
	chSysInit();

	// initialize hardware
	SEGGER_RTT_ConfigUpBuffer(0, NULL, NULL, 0, SEGGER_RTT_MODE_NO_BLOCK_TRIM);

	volatile int status;
	int32_t ret_value;

	i2cStart(&I2CD2, &imu_i2c_conf);

	coding_wheels_config_t cod_cfg = {
		0U,
		DIRECT,
		0U,
		INDIRECT
	};
	init_coding_wheels(cod_cfg);
	motor_init(DIRECTION_2, DIRECTION_2);

	status = initIMU(&I2CD2);
	if (status == NO_ERROR) {
		printf("Init OK\n");
	} else {
		printf("Error in IMU init\n");
	}

	//setFormat(RADIAN);

	/*ret_value = test_position_0010();
	if (ret_value == TEST_NO_ERROR) {
		printf("test position 0010 succeeded \r\n");
	} else {
		printf("test position 0010 failed %u \r\n", ret_value);
	}

	ret_value = test_orientation();
	if (ret_value == TEST_NO_ERROR) {
		printf("test orientation succeeded\r\n");
	} else {
		printf("test orientation failed %u \r\n", ret_value);
	}

	test_position_0020();*/

	i2c_slave_init(&I2CD1);

	chThdCreateStatic(wa_control, sizeof(wa_control), NORMALPRIO + 1, control_thread, NULL);
	chThdCreateStatic(wa_int_pos, sizeof(wa_int_pos), NORMALPRIO + 1, int_pos_thread, NULL);

	max_linear_acceleration = 5;
	max_angular_acceleration = 50;
	linear_p_coeff = 700;
	linear_i_coeff = 2;
	linear_d_coeff = 5000;
	angular_p_coeff = 1000;

	goal_mean_dist = 1000;
	//goal_heading = 1440;

	heading_dist_sync_ref = 0;
	ticks_per_m = 5250;
	wheels_gap = 150;

	cruise_linear_speed = 30;
	angular_trust_threshold = 100;

	while(TRUE) {
		chThdSleepMilliseconds(50);
		//printf("pwm left %d\r\n", left_speed);
		//printf("pwm rigth %d\r\n", right_speed);
		palTogglePad(GPIOA, GPIOA_RUN_LED);
		//printf("------------- ticks %d || %d\r\n", left_ticks, right_ticks);
	}

	chThdSleep(TIME_INFINITE);
	return 0;
}
