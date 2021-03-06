#ifndef OT_LIBERTY_TIMING_HPP_
#define OT_LIBERTY_TIMING_HPP_

#include <ot/liberty/lut.hpp>

namespace ot {

enum class TimingSense {
  NON_UNATE = 0,
  POSITIVE_UNATE,
  NEGATIVE_UNATE
};

enum class TimingType {
  COMBINATIONAL = 0,
  COMBINATIONAL_RISE,
  COMBINATIONAL_FALL,
  THREE_STATE_DISABLE,
  THREE_STATE_DISABLE_RISE,
  THREE_STATE_DISABLE_FALL,
  THREE_STATE_ENABLE,
  THREE_STATE_ENABLE_RISE,
  THREE_STATE_ENABLE_FALL,
  RISING_EDGE,
  FALLING_EDGE,
  PRESET,
  CLEAR,
  HOLD_RISING,
  HOLD_FALLING,
  SETUP_RISING,
  SETUP_FALLING,
  RECOVERY_RISING,
  RECOVERY_FALLING,
  SKEW_RISING,
  SKEW_FALLING,
  REMOVAL_RISING,
  REMOVAL_FALLING,
  MIN_PULSE_WIDTH,
  MINIMUM_PERIOD,
  MAX_CLOCK_TREE_PATH,
  MIN_CLOCK_TREE_PATH,
  NON_SEQ_SETUP_RISING,
  NON_SEQ_SETUP_FALLING,
  NON_SEQ_HOLD_RISING,
  NON_SEQ_HOLD_FALLING,
  NOCHANGE_HIGH_HIGH,
  NOCHANGE_HIGH_LOW,
  NOCHANGE_LOW_HIGH,
  NOCHANGE_LOW_LOW,
};
  
inline const std::unordered_map<std::string, TimingType> timing_types = {
  {"combinational",            TimingType::COMBINATIONAL},
  {"combinational_rise",       TimingType::COMBINATIONAL_RISE},
  {"combinational_fall",       TimingType::COMBINATIONAL_FALL},
  {"three_state_disable",      TimingType::THREE_STATE_DISABLE},
  {"three_state_disable_rise", TimingType::THREE_STATE_DISABLE_RISE},
  {"three_state_disable_fall", TimingType::THREE_STATE_DISABLE_FALL},
  {"three_state_enable",       TimingType::THREE_STATE_ENABLE},
  {"three_state_enable_rise",  TimingType::THREE_STATE_ENABLE_RISE},
  {"three_state_enable_fall",  TimingType::THREE_STATE_ENABLE_FALL},
  {"rising_edge",              TimingType::RISING_EDGE},
  {"falling_edge",             TimingType::FALLING_EDGE},
  {"preset",                   TimingType::PRESET},
  {"clear",                    TimingType::CLEAR},
  {"hold_rising",              TimingType::HOLD_RISING},
  {"hold_falling",             TimingType::HOLD_FALLING},
  {"setup_rising",             TimingType::SETUP_RISING},
  {"setup_falling",            TimingType::SETUP_FALLING},
  {"recovery_rising",          TimingType::RECOVERY_RISING},
  {"recovery_falling",         TimingType::RECOVERY_FALLING},
  {"skew_rising",              TimingType::SKEW_RISING},
  {"skew_falling",             TimingType::SKEW_FALLING},
  {"removal_rising",           TimingType::REMOVAL_RISING},
  {"removal_falling",          TimingType::REMOVAL_FALLING},
  {"min_pulse_width",          TimingType::MIN_PULSE_WIDTH},
  {"minimum_period",           TimingType::MINIMUM_PERIOD},
  {"max_clock_tree_path",      TimingType::MAX_CLOCK_TREE_PATH},
  {"min_clock_tree_path",      TimingType::MIN_CLOCK_TREE_PATH},
  {"non_seq_setup_rising",     TimingType::NON_SEQ_SETUP_RISING},
  {"non_seq_setup_falling",    TimingType::NON_SEQ_SETUP_FALLING},
  {"non_seq_hold_rising",      TimingType::NON_SEQ_HOLD_RISING},
  {"non_seq_hold_falling",     TimingType::NON_SEQ_HOLD_FALLING},
  {"nochange_high_high",       TimingType::NOCHANGE_HIGH_HIGH},
  {"nochange_high_low",        TimingType::NOCHANGE_HIGH_LOW},
  {"nochange_low_high",        TimingType::NOCHANGE_LOW_HIGH},
  {"nochange_low_low",         TimingType::NOCHANGE_LOW_LOW}
};

// Function: to_string
std::string to_string(TimingSense);
std::string to_string(TimingType);

// Struct: Timing
struct Timing {
  
  std::string related_pin;

  std::optional<TimingSense> sense;               // by default non-sense
  std::optional<TimingType> type;                 // by default combinational
  std::optional<TimingLut> cell_rise;             // Delay LUT rise (sink).
  std::optional<TimingLut> cell_fall;             // Delay LUT fall (sink).
  std::optional<TimingLut> rise_transition;       // Slew LUT rise (sink).
  std::optional<TimingLut> fall_transition;       // Slew LUT fall (sink).
  std::optional<TimingLut> rise_constraint;       // Rise constraint (sink).
  std::optional<TimingLut> fall_constraint;       // Fall constraint (sink).

  bool is_constraint() const;                     // Query the constraint status.
  bool is_hold_constraint() const;                // Query the constraint status.
  bool is_setup_constraint() const;               // Query the constraint status.
  bool is_rising_edge_triggered() const;          // Query the rising edge status.
  bool is_falling_edge_triggered() const;         // Query the falling edge status.
  bool is_input_transition_defined() const;       // Query the input transition status.
  bool is_input_transition_defined(Tran) const;   // Query the input transition status.
  bool is_output_transition_defined(Tran) const;  // Query the output transition status.
  bool is_transition_defined(Tran, Tran) const;   // Query the timing transition status.
  bool isomorphic(const Timing&) const;

  void scale_time(float);
  void scale_capacitance(float);

  std::optional<float> delay(Tran, Tran, float, float) const;
  std::optional<float> slew(Tran, Tran, float, float) const;
  std::optional<float> constraint(Tran, Tran, float, float) const;
};

std::ostream& operator << (std::ostream&, const Timing&);

// Alias
using TimingView = TimingData<const Timing*, MAX_SPLIT>;


};  // end of namespace ot. -----------------------------------------------------------------------


#endif
