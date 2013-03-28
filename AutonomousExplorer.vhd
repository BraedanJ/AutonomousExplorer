library ieee;
use ieee.std_logic_1164.all;
use ieee.std_logic_arith.all;
use ieee.std_logic_unsigned.all;

entity AutonomousExplorer is
	port
	(
		-- LEDS
      LED  		: 	out 		std_logic_vector(7 downto 0);                

      -- DRAM ports
      DRAM_CLK		: 	out 		std_logic;
		DRAM_CKE 	: 	out 		std_logic;
      DRAM_ADDR	: 	out 		std_logic_vector(12 DOWNTO 0);
      DRAM_BA		: 	out 		std_logic_vector(1 downto 0);
      DRAM_CS_N 	: 	out 		std_logic; 
		DRAM_CAS_N 	: 	out 		std_logic; 
		DRAM_RAS_N 	: 	out 		std_logic; 
		DRAM_WE_N 	: 	out 		std_logic;
      DRAM_DQ 		: 	inout 	std_logic_vector(15 DOWNTO 0);
		DRAM_DQM		:	out		std_logic_vector(1 downto 0);

		--ADC
		ADC_CS_N		:	out		std_logic;
		ADC_SADDR	:	out		std_logic;
		ADC_SCLK		:	out		std_logic;
		ADC_SDAT		:	in			std_logic;
		
      -- CLOCK port
      CLOCK_50 	:	in  		std_logic;
					 
		-- Switch			
		SW				:	in 		std_logic_vector(3 downto 0);
					 
      -- RESET key
      KEY 			:	in  		std_logic_vector(0 downto 0);
		
		--GPIO_0
		GPIO_0		:	inout		std_logic_vector(33 downto 0)
	);
end AutonomousExplorer;

architecture structure of AutonomousExplorer is

component niosII_system
        port
        (
         -- PLL ports
         altpll_sdram : out std_logic;
         altpll_system : out std_logic;
         locked_from_the_altpll_sys : out std_logic;
			phasedone_from_the_altpll_sys : out std_logic;

         -- LEDS 
			out_port_from_the_led : out std_logic_vector (7 downto 0);

         -- DRAM ports
         zs_addr_from_the_sdram : out std_logic_vector (12 DOWNTO 0);
         zs_ba_from_the_sdram : out std_logic_vector (1 DOWNTO 0);
         zs_cas_n_from_the_sdram : out std_logic;
			zs_cke_from_the_sdram : out std_logic;
         zs_cs_n_from_the_sdram : out std_logic;
         zs_dq_to_and_from_the_sdram : inout std_logic_vector (15 DOWNTO 0);
         zs_dqm_from_the_sdram : out std_logic_vector (1 DOWNTO 0);
         zs_ras_n_from_the_sdram : out std_logic;
			zs_we_n_from_the_sdram : out std_logic;

			--ADC
			SPI_CLK_from_the_adc_spi_read : out std_logic;
         SPI_CS_n_from_the_adc_spi_read : out std_logic;
         SPI_IN_to_the_adc_spi_read : in std_logic;
         SPI_OUT_from_the_adc_spi_read : out std_logic;
			
         -- CLOCK port
         clk_50           : in  std_logic;
					 
			-- SWITCH
			in_port_to_the_sw : in std_logic_vector (3 downto 0);
					 
         -- RESET Key
         reset_n : in  std_logic;
			
			
			--PWMs
			coe_pwm_output_export_from_the_PWM_left : out std_logic;
			coe_pwm_output_export_from_the_PWM_right : out std_logic;
			
			--Wheel direction
			out_port_from_the_dir_left : out std_logic;
			out_port_from_the_dir_right : out std_logic;
			
			--encoders
			coe_encoder_input_export_to_the_encoder_front_left : in std_logic;
			coe_encoder_input_export_to_the_encoder_front_right : in std_logic;
			coe_encoder_input_export_to_the_encoder_back_left : in std_logic;
			coe_encoder_input_export_to_the_encoder_back_right : in std_logic;
			
			--Sensor chain init
			out_port_from_the_chain_init : out std_logic;
			
			--I2C
			out_port_from_the_i2c_scl : out std_logic;              
         bidir_port_to_and_from_the_i2c_sda : inout std_logic
        );		  
end component;
		  
        signal pll_c1		:	std_logic;
        signal pll_locked	:	std_logic;
        signal pll_phase	:	std_logic;

begin	        
        NIOSII : niosII_system port map ( 		  
				altpll_sdram => DRAM_CLK, 
				altpll_system => pll_c1, 
				locked_from_the_altpll_sys => pll_locked,
				out_port_from_the_led => LED, 
				phasedone_from_the_altpll_sys => pll_phase,
				zs_addr_from_the_sdram => DRAM_ADDR, 
				zs_ba_from_the_sdram => DRAM_BA, 
				zs_cas_n_from_the_sdram => DRAM_CAS_N, 
				zs_cke_from_the_sdram => DRAM_CKE, 
				zs_cs_n_from_the_sdram => DRAM_CS_N,
				zs_dq_to_and_from_the_sdram => DRAM_DQ, 
				zs_dqm_from_the_sdram => DRAM_DQM, 
				zs_ras_n_from_the_sdram => DRAM_RAS_N, 
				zs_we_n_from_the_sdram => DRAM_WE_N,
				SPI_CLK_from_the_adc_spi_read => ADC_SCLK,
				SPI_CS_n_from_the_adc_spi_read => ADC_CS_N,
				SPI_IN_to_the_adc_spi_read => ADC_SDAT,
				SPI_OUT_from_the_adc_spi_read => ADC_SADDR,
				clk_50 => CLOCK_50, 
				in_port_to_the_sw => SW, 
				reset_n => KEY(0),
		  
		  
				coe_pwm_output_export_from_the_PWM_left => GPIO_0(8),
				coe_pwm_output_export_from_the_PWM_right => GPIO_0(9),
				
				out_port_from_the_dir_left => GPIO_0(10),
				out_port_from_the_dir_right => GPIO_0(11),
				
				coe_encoder_input_export_to_the_encoder_front_left => GPIO_0(2),
				coe_encoder_input_export_to_the_encoder_front_right => GPIO_0(3),
				coe_encoder_input_export_to_the_encoder_back_left => GPIO_0(4),
				coe_encoder_input_export_to_the_encoder_back_right => GPIO_0(5),
				
				out_port_from_the_chain_init => GPIO_0(20),
				
				out_port_from_the_i2c_scl => GPIO_0(33),
            bidir_port_to_and_from_the_i2c_sda => GPIO_0(32)
		  );
end structure;
