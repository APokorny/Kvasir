#include "Hardware.h"
#include "Timer.hpp"
#include "StartUp.hpp"

namespace Act = Kvasir::Gpio::Action;
namespace M = Kvasir::MPL;
namespace R = Kvasir::Register;

class Led {
public:
	using Init = decltype(M::list(action(Act::output,Hardware::ledPin)));
	static void toggle(){
		R::apply(action(Act::toggle,Hardware::ledPin));
	}
};

class Timer : public Kvasir::Timer::Base<Timer,Kvasir::Timer16B0>{
public:
	using Init = decltype(M::list(Config::clockEnable,
			R::sequencePoint,
			Config::MatchControl::r0InterruptEnable,
			Config::MatchControl::r0ResetOnMatch,
			Config::SetPrescaleT<1000000>{},
			Config::SetR0ValueT<10000000>{},
			R::sequencePoint,
			Config::couterEnable,
			Config::enableIrq
			));
	static void onMatch0(){
		Led::toggle();
	}
};


int main(){
	while(1);
	return 0;
}


KVASIR_START(Timer,Led)