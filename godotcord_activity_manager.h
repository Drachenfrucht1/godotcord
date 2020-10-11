#ifndef GODOTCORD_ACTIVITY_MANAGER_H
#define GODOTCORD_ACTIVITY_MANAGER_H

#include "core/object.h"
#include "godotcord.h"

class GodotcordActivityManager : public Object {
	GDCLASS(GodotcordActivityManager, Object);

protected:
	static void _bind_methods();

public:
	static GodotcordActivityManager *singleton;
	static GodotcordActivityManager *get_singleton();
	void init();

	void set_activity(Ref<GodotcordActivity> p_activity);
	void clear_activity();

	void send_request_reply(int64_t p_user_id, GodotcordActivity::ActivityRequestReply p_reply);
	void send_invite(int64_t p_user_id, GodotcordActivity::ActivityActionType p_type, String p_message);
	void accept_invite(int64_t p_user_id);

	GodotcordActivityManager();
	~GodotcordActivityManager();
};

#endif //GODOTCORD_ACTIVITY_MANAGER_H
