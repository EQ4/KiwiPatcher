/*
 ==============================================================================
 
 This file is part of the KIWI library.
 Copyright (c) 2014 Pierre Guillot & Eliott Paris.
 
 Permission is granted to use this software under the terms of either:
 a) the GPL v2 (or any later version)
 b) the Affero GPL v3
 
 Details of these licenses can be found at: www.gnu.org/licenses
 
 KIWI is distributed in the hope that it will be useful, but WITHOUT ANY
 WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR
 A PARTICULAR PURPOSE.  See the GNU General Public License for more details.
 
 ------------------------------------------------------------------------------
 
 To release a closed-source product which uses KIWI, contact : guillotpierre6@gmail.com
 
 ==============================================================================
*/

#include "KiwiFactory.h"
#include "KiwiConsole.h"
#include "../KiwiObjects/KiwiObjects.h"

namespace Kiwi
{
    // ================================================================================ //
    //                                      FACTORY                                     //
    // ================================================================================ //
    
    sObject Factory::create(const sTag name, Infos const& detail)
    {
        lock_guard<mutex> guard(getMutex());
        map<sTag, sCreator>& creators(getCreators());
        auto it = creators.find(name);
        if(it != creators.end())
        {
            sObject obj = it->second->create(detail);
            if(obj)
            {
                obj->read(detail.dico);
            }
            return obj;
        }
        else
        {
            Console::error("The factory doesn't know the object " + name->getName());
            return nullptr;
        }
    }
    
    bool Factory::has(const sTag name)
    {
        lock_guard<mutex> guard(getMutex());
        map<sTag, sCreator>& creators(getCreators());
        return creators.find(name) != creators.end();
    }
    
    void Factory::remove(const sTag name)
    {
        lock_guard<mutex> guard(getMutex());
        map<sTag, sCreator>& creators(getCreators());
        creators.erase(name);
    }
    
    vector<sTag> Factory::names()
    {
        lock_guard<mutex> guard(getMutex());
        vector<sTag> names;
        for(auto it : getCreators())
        {
            names.push_back(it.first);
        }
        return names;
    }
}

