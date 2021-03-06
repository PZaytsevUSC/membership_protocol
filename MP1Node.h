/**********************************
 * FILE NAME: MP1Node.cpp
 *
 * DESCRIPTION: Membership protocol run by this Node.
 * 				Header file of MP1Node class.
 **********************************/

#ifndef _MP1NODE_H_
#define _MP1NODE_H_

#include "stdincludes.h"
#include "Log.h"
#include "Params.h"
#include "Member.h"
#include "EmulNet.h"
#include "Queue.h"
#include <stdlib.h>
#include <time.h> 
#include <algorithm>
/**
 * Macros
 */
#define TREMOVE 20
#define TFAIL 5

/*
 * Note: You can change/add any functions in MP1Node.{h,cpp}
 */

/**
 * Message Types
 */
enum MsgTypes{
    JOINREQ,
    JOINREP,
    DUMMYLASTMSGTYPE
};

/**
 * STRUCT NAME: MessageHdr
 *
 * DESCRIPTION: Header and content of a message
 */
typedef struct MessageHdr {
	enum MsgTypes msgType;
    long memberCount = 0;
}MessageHdr;


typedef struct Message {
    MessageHdr hdr;
    Address from;
    vector<MemberListEntry> members;
public:
    Message() {
        allocateMembers(1);
    }
    
    Message(int membersCount) {
        allocateMembers(membersCount);
    }
    
    void allocateMembers(int membersCount) {
        members.reserve(membersCount);
    }
    
} Message;

/**
 * CLASS NAME: MP1Node
 *
 * DESCRIPTION: Class implementing Membership protocol functionalities for failure detection
 */
class MP1Node {
private:
	EmulNet *emulNet;
	Log *log;
	Params *par;
	Member *memberNode;
	char NULLADDR[6];

public:
	MP1Node(Member *, Params *, EmulNet *, Log *, Address *);
	Member * getMemberNode() {
		return memberNode;
	}
    int gossip_beta = 3;
    long localTimeStamp = 0;
	int recvLoop();
    Address & myAddress();
    vector <MemberListEntry> get_gossip_targets();
    void add_to_my_membership_list(Address & addr);
    void recordMembers(Message *incomingMsg, Address &from);
    void get_id_port(Address * addr, int &id, short &port);
    void acknowledge_join_response(Message * msg, Address & addr);
    void replyToJoin(Address &from);
	static int enqueueWrapper(void *env, char *buff, int size);
	void nodeStart(char *servaddrstr, short serverport);
	int initThisNode(Address *joinaddr);
	int introduceSelfToGroup(Address *joinAddress);
	int finishUpThisNode();
	void nodeLoop();
	void checkMessages();
	bool recvCallBack(void *env, char *data, int size);
	void nodeLoopOps();
	int isNullAddress(Address *addr);
	Address getJoinAddress();
	void initMemberListTable(Member *memberNode);
	void printAddress(Address *addr);
	virtual ~MP1Node();
};

#endif /* _MP1NODE_H_ */
