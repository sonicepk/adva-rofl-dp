#ifndef ETHERSWITCH_H
#define ETHERSWITCH_H 1
#endif

#include <map>
#include "rofl/common/cmacaddr.h"
#include "rofl/common/caddress.h"
#include "rofl/common/crofbase.h"
#include "rofl/common/openflow/cofdpt.h"
#include <rofl/common/utils/c_logger.h>
#include <fstream>
extern "C"{
	#include "../../adva-agent-rofl/Agent/Agent.h"
}

#include <cfib.h>

using namespace rofl;

namespace etherswitch
{

class ethswitch :
		public crofbase
{
private:

#if 0
	struct fibentry_t {
		uint32_t 		port_no;	// port where a certain is attached
		time_t 			timeout;	// timeout event for this FIB entry
	};

	// a very simple forwarding information base
	std::map<cofdpt*, std::map<uint16_t, std::map<cmacaddr, struct fibentry_t> > > fib;

	unsigned int 		fib_check_timeout; 		// periodic timeout for removing expired FIB entries
	unsigned int		flow_stats_timeout;		// periodic timeout for requesting flow stats
	unsigned int		fm_delete_all_timeout;	// periodic purging of all FLOW-MODs
#endif

	X_CorePtr core_ptr;

	enum etherswitch_timer_t {
		ETHSWITCH_TIMER_BASE 					= ((0x6271)),
		ETHSWITCH_TIMER_FIB 					= ((ETHSWITCH_TIMER_BASE) + 1),
		ETHSWITCH_TIMER_FLOW_STATS 				= ((ETHSWITCH_TIMER_BASE) + 2),
		ETHSWITCH_TIMER_FLOW_MOD_DELETE_ALL 	= ((ETHSWITCH_TIMER_BASE) + 3),
	};

public:

	ethswitch(X_CorePtr _core_ptr);

	virtual	~ethswitch();

	virtual void handle_ctrl_open(rofl::cofctl *ctl);

	virtual void handle_dpath_open(rofl::cofdpt *dpt);

	virtual void handle_features_request (cofctl *ctl, cofmsg_features_request *msg);

	virtual void handle_ctrl_close(rofl::cofctl *ctl);

private:

	void
	request_flow_stats();
}; // end of class ethswitch

}; // end of namespace
