// adapted from http://allmybrain.com/2008/06/10/timing-cc-code-on-linux/
/**************************************************************************
*   Copyright (C) 2010 by Mark Pictor                                     *
*   mpictor@gmail.com                                                     *
*                                                                         *
*   This program is free software; you can redistribute it and/or modify  *
*   it under the terms of the GNU General Public License as published by  *
*   the Free Software Foundation; either version 2 of the License, or     *
*   (at your option) any later version.                                   *
*                                                                         *
*   This program is distributed in the hope that it will be useful,       *
*   but WITHOUT ANY WARRANTY; without even the implied warranty of        *
*   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the         *
*   GNU General Public License for more details.                          *
*                                                                         *
*   You should have received a copy of the GNU General Public License     *
*   along with this program; if not, write to the                         *
*   Free Software Foundation, Inc.,                                       *
*   59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.             *
**************************************************************************/
#ifndef NANOTIMER_HH
#define NANOTIMER_HH

#include <QString>

#include <time.h>
#include <string>

class Nanotimer {
  private:
    timespec begin;
  public:
    Nanotimer() {}
    void start() {clock_gettime(CLOCK_MONOTONIC_RAW, &begin);}
    long getElapsed() {
      timespec now,delta;
      clock_gettime(CLOCK_MONOTONIC_RAW, &now);
      delta.tv_sec = now.tv_sec - begin.tv_sec;
      delta.tv_nsec = now.tv_nsec - begin.tv_nsec;
      return delta.tv_sec*1000000000 + delta.tv_nsec;
    }
    double getElapsedS() {
      timespec now,delta;
      clock_gettime(CLOCK_MONOTONIC_RAW, &now);
      delta.tv_sec = now.tv_sec - begin.tv_sec;
      delta.tv_nsec = now.tv_nsec - begin.tv_nsec;
      return delta.tv_sec + delta.tv_nsec/1000000000.0;
    }
    QString str() {
        return humanreadable( getElapsedS() );
    }
    static QString humanreadable(double s) {
      QString out;
      if (s > 60) {
        int m;
        m = s/60;
        s = s-(double)(m*60);
        out = QString::number(m)  + QString("m, ");
      }
      if (s > .5) {
        out += QString::number(s); 
        out += QString(" s");
      } else if (s> 0.0005) {
        out = QString::number(s*1000); 
        out += QString(" ms");
      } else {
        out = QString::number(s*1000000); 
        out += QString(" us");
      }
      return out;
    }
};

#endif //NANOTIMER_HH
