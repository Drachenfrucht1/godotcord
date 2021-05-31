#ifndef GODOTCORD_NETWORK_PEER_H
#define GODOTCORD_NETWORK_PEER_H

#include "core/io/networked_multiplayer_peer.h"
#include "discord-files/discord.h"
#include "godotcord.h"

class GodotcordPeer: public Reference {
	GDCLASS(GodotcordPeer, Reference)
public:
	int64_t discord_id = 0;					///< discord user id
	uint64_t discord_peer_id = 0;
	int target_id = 0;						///< godot peer id
	bool confirmed = false;
	//needed in order for list (and set?) to work
	bool operator==(const GodotcordPeer& p2) {
		bool r;
		(this->discord_id == p2.discord_id && this->discord_peer_id == p2.discord_peer_id && this->target_id == p2.target_id) ? r = true : r = false;
		return r;
	}
};

class NetworkedMultiplayerGodotcord : public NetworkedMultiplayerPeer {
	GDCLASS(NetworkedMultiplayerGodotcord, NetworkedMultiplayerPeer)
public:

    List<Ref<GodotcordPeer>> _peers;
private:
	discord::LobbyManager *_lobby_manager;
	discord::NetworkManager *_network_manager;
	int64_t _lobby_id;							///< id of the joined discord lobby
	static int64_t local_user_id;				///< discord user id
	static uint64_t unique_peer_id;				///< discord peer id
	static String route;
	int _unique_id;								///< localy generated godot peer id 

	bool _active;
	bool _server;

	int _target_peer;							///< godot peer id of the target of the next packet to be send
	TransferMode _transfer_mode;
	int _transfer_channel;
	int _channel_count;

	bool _refuse_connections;

	ConnectionStatus _connection_status;

	struct Packet {
		uint8_t *data;
		int size;
		int from;
		int channel;
	};

	List<Packet> _incomming_packets;
	List<Packet> _defered_packets;
	List<Packet> _service_packets;

	Packet _current_packet;

	void _pop_current_packet();
	uint32_t _gen_unique_id() const;

	Ref<GodotcordPeer> _setup_peer(int64_t p_user_id, bool confirm);
	void _store_connection_details();

	void _send_packet(Ref<GodotcordPeer> peer, uint8_t *data, uint8_t channel, uint32_t size);
	void _resend_messages();

	Ref<GodotcordPeer> _get_peer_by_discord_peer_id(uint64_t p_peer_id);
	Ref<GodotcordPeer> _get_peer_by_discord_id(int64_t p_user_id);
	Ref<GodotcordPeer> _get_peer_by_target_id(int p_target_id);

protected:
	static void _bind_methods();

public:
	virtual void set_transfer_mode(TransferMode p_mode);
	virtual TransferMode get_transfer_mode() const;
	virtual void set_target_peer(int p_peer);

    virtual Array get_connected_peers();

	virtual int get_packet_peer() const;

	Error create_lobby(int size, bool pub = false);
	Error join_lobby(int64_t id, String secret);
	Error join_lobby_activity(String activitySecret);

	void close_connection();
	void delete_lobby();

	void disconnect_peer(int p_peer);

	virtual void poll();

	virtual bool is_server() const;

	virtual int get_available_packet_count() const;
	virtual Error get_packet(const uint8_t **r_buffer, int &r_buffer_size);
	virtual Error put_packet(const uint8_t *p_buffer, int p_buffer_size);

	virtual int get_max_packet_size() const;

	virtual ConnectionStatus get_connection_status() const;

	virtual void set_refuse_new_connections(bool p_enable);
	virtual bool is_refusing_new_connections() const;

	virtual int get_unique_id() const;

	//Some methods from Enet implemtation missing - adding when needed

	void set_public(bool p_public);
	void set_size(int size);

	void set_metadata(String key, String value);
	String get_metadata(String key);

	int get_lobby_id() const;
	String get_lobby_secret() const;
	String get_lobby_activity_secret() const;
	int get_current_members() const;
	int get_max_members() const;
	int64_t get_user_id_by_peer(int p_target_id);
	int get_peer_id_by_user(int64_t p_user_id);

	NetworkedMultiplayerGodotcord();
	~NetworkedMultiplayerGodotcord();
};

#endif
