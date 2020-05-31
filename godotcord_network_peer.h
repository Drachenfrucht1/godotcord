#ifndef GODOTCORD_NETWORK_PEER_H
#define GODOTCORD_NETWORK_PEER_H

#include "core/io/networked_multiplayer_peer.h"
#include "discord-files/discord.h"
#include "godotcord.h"

class NetworkedMultiplayerDiscord : public NetworkedMultiplayerPeer {
	GDCLASS(NetworkedMultiplayerDiscord, NetworkedMultiplayerPeer)

private:
	discord::LobbyManager *lobby_manager;
	int lobby_id;

	bool active;
	bool server;

	uint32_t unique_id;
	int target_peer;
	TransferMode transfer_mode;
	int transfer_channel;
	int channel_count;

	bool refuse_connections;

	ConnectionStatus connection_status;

	struct Packet {
		uint8_t *data;
		int size;
		int from;
		int channel;
	};

	List<Packet> incomming_packets;

	Packet current_packet;

	enum LobbyRole {
		SERVER,
		USER
	};

	List<int64_t> peers;
	int64_t server_peer;

	void _pop_current_packet();


protected:
	static void _bind_methods();

public:
	void init_discord(Ref<Godotcord> discord);

	virtual void set_transfer_mode(TransferMode p_mode);
	virtual TransferMode get_transfer_mode() const;
	virtual void set_target_peer(int p_peer);

	virtual int get_packet_peer() const;

	Error create_lobby(int size, bool pub = false);
	Error join_lobby(int id, String secret);
	Error join_lobby_activity(String activitySecret);

	void close_connection();

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

	int get_lobby_id() const;
	String get_lobby_secret();
	String get_lobby_activity_secret();

	NetworkedMultiplayerDiscord();
	~NetworkedMultiplayerDiscord();
};

#endif
