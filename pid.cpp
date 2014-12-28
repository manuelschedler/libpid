#include <iostream>
#include <fstream>
#include "pid.h"

PID::PID(double soll, unsigned int maxsize, double *pid) {
  setpid(pid);
  _nvals=0;
  _integralstatic=0;
  _maxsize=maxsize;
  _max=0;
  _min=0;
  setsoll(soll);
  _debug=0;
};

PID::PID(double soll, unsigned int maxsize) {
  PID(soll, maxsize, NULL);
}

PID::PID(double soll) {
  PID(soll,2);
}

PID::PID(double *pid) {
  PID(0, 2, pid);
}

PID::PID(unsigned int maxsize) {
  PID(0,maxsize);
}

PID::PID() {
  PID(0,2);
}
PID::~PID() {
  if(_debug>0) {
    std::cout << "### DEBUG1: Klasse gelöscht" << std::endl;
  }
  if(_out!=NULL) {
    _out.close();
  }
};

void PID::setsoll(double soll) {
  _soll=soll;
  if(_debug>0) {
    std::cout << "### DEBUG1: Setze Sollwert auf " << _soll << std::endl;
  }
};

void PID::setpid(double *pid) {
  if(pid!=NULL) {
    for(unsigned int i=0; i<3; i++) {
      _pid[i]=pid[i];
    }
  }
  else {
    for(unsigned int i=0; i<3; i++) {
      _pid[i]=0;
    }
  }
  coeff();
};

void PID::setout(std::string name) {
  _out.open(name.c_str());
}

void PID::setmax(double max) {
  _max=max;
}

void PID::setmin(double min) {
  _min=min;
}

void PID::setdebug(double debug) {
  _debug=debug;
}

double PID::push_back(double ist) {
  _delta2=_delta;
  _delta=ist-_soll;
  _integralstatic+=_delta;
  if(_debug>2) {
    std::cout << "### DEBUG3: _delta=" << _delta << std::endl;
  }
  _process();
  return _setpoint;
}

double PID::operator<<(double data) {
  return push_back(data);
}

void PID::_process() {
  _setpoint=0;
  _proportional();
  _integral();
  _differential();
  ist();
};

void PID::_proportional() {
  if(_pid[0]!=0) {
    _setpoint=_delta*_pid[0];
  }
};

void PID::_integral() {
  if(_pid[1]!=0) {
    _setpoint+=_integralstatic*_pid[1];
  }
};

void PID::_differential() {
  if(_pid[2]!=0) {
    _setpoint+=(_delta-_delta2)*_pid[2];
  }
};

const double PID::ist() {
  if(_max!=_min) {
    if(_setpoint > _max) _setpoint=_max;
    if(_setpoint < _min) _setpoint=_min;
  }
  if(_debug>2) {
    std::cout << "### DEBUG3: _setpoint=" << _setpoint << std::endl;
  }
  if(_out!=NULL) {
    _out << _delta << "\t" << _setpoint << std::endl;
  }
  return _setpoint;
}

const double *PID::coeff() {
  static double pid[3];
  for(unsigned int i=0; i<3; i++) {
    pid[i]=_pid[i];
  }
  if(_debug>1) {
    std::cout << "### DEBUG2: _pid={" << _pid[0] << ", " << _pid[1] << ", " << pid[2] << "}" << std::endl;
  }
  return pid;
}
