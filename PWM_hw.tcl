# TCL File Generated by Component Editor 10.1sp1
# Thu Mar 14 14:49:16 MDT 2013
# DO NOT MODIFY


# +-----------------------------------
# | 
# | PWM "PWM" v1.0
# | null 2013.03.14.14:49:16
# | 
# | 
# | /afs/ualberta.ca/home/j/o/jongeriu/Desktop/AutonomousExplorer/PWM.vhd
# | 
# |    ./PWM.vhd syn, sim
# | 
# +-----------------------------------

# +-----------------------------------
# | request TCL package from ACDS 10.1
# | 
package require -exact sopc 10.1
# | 
# +-----------------------------------

# +-----------------------------------
# | module PWM
# | 
set_module_property NAME PWM
set_module_property VERSION 1.0
set_module_property INTERNAL false
set_module_property OPAQUE_ADDRESS_MAP true
set_module_property DISPLAY_NAME PWM
set_module_property TOP_LEVEL_HDL_FILE PWM.vhd
set_module_property TOP_LEVEL_HDL_MODULE pwm
set_module_property INSTANTIATE_IN_SYSTEM_MODULE true
set_module_property EDITABLE true
set_module_property ANALYZE_HDL TRUE
# | 
# +-----------------------------------

# +-----------------------------------
# | files
# | 
add_file PWM.vhd {SYNTHESIS SIMULATION}
# | 
# +-----------------------------------

# +-----------------------------------
# | parameters
# | 
# | 
# +-----------------------------------

# +-----------------------------------
# | display items
# | 
# | 
# +-----------------------------------

# +-----------------------------------
# | connection point myclock
# | 
add_interface myclock clock end
set_interface_property myclock clockRate 0

set_interface_property myclock ENABLED true

add_interface_port myclock csi_myclock_clk clk Input 1
add_interface_port myclock csi_myclock_reset reset Input 1
# | 
# +-----------------------------------

# +-----------------------------------
# | connection point pwm
# | 
add_interface pwm avalon end
set_interface_property pwm addressAlignment DYNAMIC
set_interface_property pwm addressUnits WORDS
set_interface_property pwm associatedClock myclock
set_interface_property pwm burstOnBurstBoundariesOnly false
set_interface_property pwm explicitAddressSpan 0
set_interface_property pwm holdTime 0
set_interface_property pwm isMemoryDevice false
set_interface_property pwm isNonVolatileStorage false
set_interface_property pwm linewrapBursts false
set_interface_property pwm maximumPendingReadTransactions 0
set_interface_property pwm printableDevice false
set_interface_property pwm readLatency 0
set_interface_property pwm readWaitTime 1
set_interface_property pwm setupTime 0
set_interface_property pwm timingUnits Cycles
set_interface_property pwm writeWaitTime 0

set_interface_property pwm ENABLED true

add_interface_port pwm avs_pwm_write_n write_n Input 1
add_interface_port pwm avs_pwm_chipselect chipselect Input 1
add_interface_port pwm avs_pwm_address address Input 2
add_interface_port pwm avs_pwm_readdata readdata Output 32
add_interface_port pwm avs_pwm_writedata writedata Input 32
# | 
# +-----------------------------------

# +-----------------------------------
# | connection point pwm_output
# | 
add_interface pwm_output conduit end

set_interface_property pwm_output ENABLED true

add_interface_port pwm_output coe_pwm_output_export export Output 1
# | 
# +-----------------------------------
