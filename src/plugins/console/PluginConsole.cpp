/*********************************************************************
 * Software License Agreement (BSD License)
 *
 *  Copyright (c) 2014, Institute for Artificial Intelligence,
 *  Universität Bremen.
 *  All rights reserved.
 *
 *  Redistribution and use in source and binary forms, with or without
 *  modification, are permitted provided that the following conditions
 *  are met:
 *
 *   * Redistributions of source code must retain the above copyright
 *     notice, this list of conditions and the following disclaimer.
 *   * Redistributions in binary form must reproduce the above
 *     copyright notice, this list of conditions and the following
 *     disclaimer in the documentation and/or other materials provided
 *     with the distribution.
 *   * Neither the name of the Institute for Artificial Intelligence,
 *     Universität Bremen, nor the names of its contributors may be
 *     used to endorse or promote products derived from this software
 *     without specific prior written permission.
 *
 *  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 *  "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 *  LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS
 *  FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE
 *  COPYRIGHT OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT,
 *  INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING,
 *  BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 *  LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
 *  CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 *  LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN
 *  ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 *  POSSIBILITY OF SUCH DAMAGE.
 *********************************************************************/

/** \author Jan Winkler */


#include <plugins/console/PluginConsole.h>


namespace beliefstate {
  namespace plugins {
    PLUGIN_CLASS::PLUGIN_CLASS() {
      this->setPluginVersion("0.1");
    }
    
    PLUGIN_CLASS::~PLUGIN_CLASS() {
    }
    
    Result PLUGIN_CLASS::init(int argc, char** argv) {
      Result resInit = defaultResult();
      
      this->initCurses();
      this->printInterface();
      
      // Subscribe to events here.
      
      return resInit;
    }
    
    void PLUGIN_CLASS::initCurses() {
      m_winMain = initscr();
      m_winLog = newwin(4, 4, 1, 1);
      
      noecho();
      keypad(m_winMain, true);
      scrollok(m_winMain, true);
      timeout(0.01);
    }
    
    void PLUGIN_CLASS::deinitCurses() {
      endwin();
    }
    
    void PLUGIN_CLASS::printInterface() {
      box(m_winMain, 0, 0);
      
      wrefresh(m_winMain);
      wrefresh(m_winLog);
    }
    
    bool PLUGIN_CLASS::checkScreenSize() {
      int nScreenWidth, nScreenHeight;
      
      getmaxyx(stdscr, nScreenHeight, nScreenWidth);
      
      if(nScreenWidth != m_nScreenWidth || nScreenHeight != m_nScreenHeight) {
	// Screen size changed
	m_nScreenWidth = nScreenWidth;
	m_nScreenHeight = nScreenHeight;
	
	wresize(m_winMain, m_nScreenHeight, m_nScreenWidth);
	wresize(m_winLog, m_nScreenHeight - 2, m_nScreenWidth - 2);
	
	return true;
      }
      
      return false;
    }
    
    Result PLUGIN_CLASS::deinit() {
      deinitCurses();
      
      return defaultResult();
    }
    
    Result PLUGIN_CLASS::cycle() {
      Result resCycle = defaultResult();
      
      if(this->checkScreenSize()) {
	this->printInterface();
      }
      
      this->deployCycleData(resCycle);
      
      return resCycle;
    }
    
    void PLUGIN_CLASS::consumeEvent(Event evEvent) {
      // Handle events here.
    }
  }
  
  extern "C" plugins::PLUGIN_CLASS* createInstance() {
    return new plugins::PLUGIN_CLASS();
  }
  
  extern "C" void destroyInstance(plugins::PLUGIN_CLASS* icDestroy) {
    delete icDestroy;
  }
}
