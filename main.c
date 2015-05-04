#include "bsp.h"
#include "setup.h"

void main(void) {

	uint8_t pk_opposition = 25;
	uint8_t pk_self = 6;
	char pk_opp_name[20];
	char pk_self_name[20];
	char attack1[15], attack2[15], attack3[15], attack4[15];

	setup_lcd_fs();
	setup_timer_buttons();

	//	init_touch_adc();

	pokemon_data_t pokemon_opposition, pokemon_self;
	pokemon_team_t pkt_opposition, pkt_self;

	for (pk_opposition=1; pk_opposition<=26; pk_opposition++) {
		pokemon_opposition = get_pokemon_data(pk_opposition);
		pokemon_self = get_pokemon_data(pk_self);

		// get image here
		get_pokemon_image(pk_opposition, SIDE_OPPOSITION);
		get_pokemon_image(pk_self, SIDE_SELF);
		draw_borders();

		pkt_opposition = get_pokemon_team(pk_opposition);

		get_attack_Name(pkt_opposition.attackOne, attack1);
		set_button1_text(attack1);
		get_attack_Name(pkt_opposition.attackTwo, attack2);
		set_button2_text(attack2);
		get_attack_Name(pkt_opposition.attackThree, attack3);
		set_button3_text(attack3);
		get_attack_Name(pkt_opposition.attackFour, attack4);
		set_button4_text(attack4);

		draw_health(100, 100);

		get_Name(pk_opposition, pk_opp_name);
		get_Name(pk_self, pk_self_name);
		draw_names(pk_self_name, pk_opp_name);

		updateButtons();

		while (!getFlag(flgupdateButton));
		clearFlag(flgupdateButton);
	}

	while(1){
		if (getFlag(flgupdateButton)){
			updateButtons();
			clearFlag(flgupdateButton);
		}
		if (getFlag(flgButtonSelected)){
			// do things with selected button
			P1OUT ^= 1;
			clearFlag(flgButtonSelected);
		}
	}

}
