#ifndef __REACTOR_H_
#define __REACTOR_H_
#include "macros.h"
#include "udt.h"
#include "ireactor.h"

NMS_BEGIN(kevent)

class Reactor {
public:
	Reactor(IReactor *reactor, bool del) : _del(del), _impl(reactor) {}

	~Reactor() { if (_del) safe_delete(_impl); }

	int32 begin_handle_events(timet interval = 50) { _impl->deactive(true); while (_impl->is_active()) _impl->handle_events(interval); return 0; }
	
	void end_handle_events(bool active = false) { _impl->deactive(active); }

	bool is_active() { return _impl->is_active(); }

	int32 register_handler(IHandler *handler, int32 mask) { return _impl->register_handler(handler, mask); }

	int32 register_handler(int32 sig_num, IHandler *handler) { return _impl->register_handler(sig_num, handler); }

	int32 remove_handler(int32 hid) { return _impl->remove_handler(hid); }

	int32 suspend_handler(int32 hid) { return _impl->suspend_handler(hid); }

	int32 resume_handler(int32 hid) { return _impl->resume_handler(hid); }

	int32 register_timer(IHandler *handler, timet start_time, timet interval) { return _impl->register_timer(handler, start_time, interval); }

	int32 cancel_timer(int32 tid) { return _impl->cancel_timer(tid); }

	IReactor* impl() { return _impl; }

private:
	bool _del;
	IReactor *_impl;
};

NMS_END // end namespace kevent


#endif // __REACTOR_H_

