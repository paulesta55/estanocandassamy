/** 
 * @file UserService.cpp
 * @author Philippe-Henri Gosselin
 * @date 9 décembre 2015
 * @copyright CNRS
 */

#include "UserService.hpp"
using namespace server;
using namespace std;

UserService::UserService(UserDB &userDB) : AbstractService("/user"),
                                           userDB(userDB)
{
}

HttpStatus UserService::get(Json::Value &out, int id) const
{
    if (id != 0)
    {
        const User *user = userDB.getUser(id);
        if (!user)
            throw ServiceException(HttpStatus::NOT_FOUND, "Invalid user id");
        out["idPoke"] = user->idPoke;
        out["orientation"] = user->orientation;
        out["currentLife"] = user->currentLife;
        out["x"] = user->x;
        out["y"] = user->y;
        return HttpStatus::OK;
    }
    else
    {
        int status = userDB.getStatus();
        cout << status << endl;
        if (status<0)
            throw ServiceException(HttpStatus::NOT_FOUND, "Invalid status id");
        out["status"] = status;
        return HttpStatus::OK;
    }
}

HttpStatus UserService::post(const Json::Value &in, int id)
{
    const User *user = userDB.getUser(id);
    if (!user)
        throw ServiceException(HttpStatus::NOT_FOUND, "Invalid user id");
    unique_ptr<User> usermod(new User(*user));
    if (in.isMember("orientation"))
    {
        usermod->orientation = in["orientation"].asInt();
    }
    if (in.isMember("currentLife"))
    {
        usermod->currentLife = in["currentLife"].asInt();
    }
    if (in.isMember("x"))
    {
        usermod->x = in["x"].asInt();
    }
    if (in.isMember("y"))
    {
        usermod->y = in["y"].asInt();
    }
    if (in.isMember("idPoke"))
    {
        usermod->idPoke = in["idPoke"].asInt();
    }
    userDB.setUser(id, std::move(usermod));
    return HttpStatus::NO_CONTENT;
}

HttpStatus UserService::put(Json::Value &out, const Json::Value &in)
{
    int x = in["x"].asInt();
    int y = in["y"].asInt();
    int orientation = in["orientation"].asInt();
    int currentLife = in["currentLife"].asInt();
    int idPoke = in["idPoke"].asInt();
    out["id"] = userDB.addUser(make_unique<User>(idPoke,orientation, currentLife, x, y));
    return HttpStatus::CREATED;
}

HttpStatus UserService::remove(int id)
{
    const User *user = userDB.getUser(id);
    if (!user)
        throw ServiceException(HttpStatus::NOT_FOUND, "Invalid user id");
    userDB.removeUser(id);
    return HttpStatus::NO_CONTENT;
}
