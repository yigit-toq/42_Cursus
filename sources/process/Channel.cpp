/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Channel.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ytop <ytop@student.42kocaeli.com.tr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/27 16:52:55 by ytop              #+#    #+#             */
/*   Updated: 2025/07/20 18:37:33 by ytop             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Channel.hpp"
#include "Server.hpp" // IRCServer'ın tam tanımına erişmek için dahil et
#include "Client.hpp"      // User sınıfının tam tanımına erişmek için dahil et

Channel::Channel(const std::string& name, Server& server)
    : _name(name), _user_limit(0), _invite_only(false), _topic_set_by_op(false), _server(server) {
    // Kurucu varsayılan değerleri ayarlar
    std::cout << "Channel " << _name << " created." << std::endl;
}

Channel::~Channel() {
    std::cout << "Channel " << _name << " destroyed." << std::endl;
}

// Getter Metotları
const std::string& Channel::getName() const { return _name; }
const std::string& Channel::getTopic() const { return _topic; }
const std::string& Channel::getPassword() const { return _password; }
size_t Channel::getUserLimit() const { return _user_limit; }
bool Channel::isInviteOnly() const { return _invite_only; }
bool Channel::isTopicSetByOp() const { return _topic_set_by_op; }

// Kullanıcılar ve Operatörler için
bool Channel::isUserInChannel(Client* user) const {
    if (!user) return false;
    return _users.count(user->GetFD()) > 0;
}

bool Channel::isOperator(Client* user) const {
    if (!user) return false;
    return _operators.count(user->GetFD()) > 0;
}

const std::map<int, Client*>& Channel::getUsers() const { return _users; }
const std::map<int, Client*>& Channel::getOperators() const { return _operators; }

// Setter Metotları (modlar için)
void Channel::setTopic(const std::string& topic, Client* setter) {
    _topic = topic;
    std::cout << "Channel " << _name << " topic set to: '" << _topic << "'";
    if (setter) {
        std::cout << " by " << setter->GetNickName();
    }
    std::cout << std::endl;
    // TOPIC komutunu implemente ettiğimizde buraya broadcast eklenecek.
}

void Channel::setPassword(const std::string& password) {
    _password = password;
    std::cout << "Channel " << _name << " password set." << std::endl;
}

void Channel::setUserLimit(size_t limit) {
    _user_limit = limit;
    std::cout << "Channel " << _name << " user limit set to: " << _user_limit << std::endl;
}

void Channel::setInviteOnly(bool status) {
    _invite_only = status;
    std::cout << "Channel " << _name << " invite-only status set to: " << (status ? "true" : "false") << std::endl;
}

void Channel::setTopicSetByOp(bool status) {
    _topic_set_by_op = status;
    std::cout << "Channel " << _name << " topic-set-by-op status set to: " << (status ? "true" : "false") << std::endl;
}

// Kanal Üyeliği Metotları
void Channel::addUser(Client* user) {
    if (!user || isUserInChannel(user)) {
        return; // Kullanıcı zaten kanalda veya geçersiz kullanıcı
    }
    _users[user->GetFD()] = user;
    std::cout << "User " << user->GetNickName() << " added to channel " << _name << std::endl;

    // Kanala katılan ilk kullanıcıyı operatör yapabiliriz (isteğe bağlı)
    if (_users.size() == 1) {
        addOperator(user);
    }
    // Katılanlara JOIN mesajı broadcast edilecek (JOIN komutunda)
}

void Channel::removeUser(Client* user) {
    if (!user || !isUserInChannel(user)) {
        return; // Kullanıcı kanalda değil veya geçersiz kullanıcı
    }
    removeOperator(user); // Operatörlüğünü kaldır (eğer operatörse)
    _users.erase(user->GetFD());
    std::cout << "User " << user->GetNickName() << " removed from channel " << _name << std::endl;
    // Ayrılanlara PART mesajı broadcast edilecek (PART/QUIT komutunda)
}

void Channel::addOperator(Client* user) {
    if (!user || !isUserInChannel(user) || isOperator(user)) {
        return; // Kullanıcı kanalda değil veya zaten operatör
    }
    _operators[user->GetFD()] = user;
    std::cout << "User " << user->GetNickName() << " is now an operator in " << _name << std::endl;
    // MOD +o komutunda bunu diğerlerine de bildireceğiz.
}

void Channel::removeOperator(Client* user) {
    if (!user || !isOperator(user)) {
        return; // Kullanıcı operatör değil
    }
    _operators.erase(user->GetFD());
    std::cout << "User " << user->GetNickName() << " is no longer an operator in " << _name << std::endl;
}

// Kanal İletişimi
void Channel::broadcastMessage(const std::string& message, Client* exclude_user) {
    for (std::map<int, Client*>::iterator it = _users.begin(); it != _users.end(); ++it) {
        Client* target_user = it->second;
        if (target_user != exclude_user) {
            target_user->AppendToOuputBuffer(message + "\r\n"); // Mesajın sonuna CRLF ekle
        }
    }
    std::cout << "Broadcasted message to channel " << _name << ": [" << message << "]" << std::endl;
}

// Kanal durumu kontrol metotları
bool Channel::isFull() const {
    return _user_limit > 0 && _users.size() >= _user_limit;
}

bool Channel::isEmpty() const {
    return _users.empty();
}
