#ifndef GODOTCORD_APPLICATIONS_MANAGER
#define GODOTCORD_APPLICATIONS_MANAGER

#include "core/object.h"

class GodotcordApplicationsManager : public Object {
    GDCLASS(GodotcordApplicationsManager, Object);

protected:
    static void _bind_methods();

public:
	static GodotcordApplicationsManager *singleton;
	static GodotcordApplicationsManager *get_singleton();

	String get_current_locale();
	String get_current_branch();

	void get_oauth2_token(Object *p_object, StringName p_funcname);

	void validate_or_exit();

	void get_ticket(Object *p_object, StringName p_funcname);

    GodotcordApplicationsManager();
    ~GodotcordApplicationsManager() {}
};

#endif //GODOTCORD_APPLICATIONS_MANAGER
