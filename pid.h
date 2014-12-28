#ifndef __pid_h__
#define __pid_h__

#include <fstream>
#include <iostream>

class PID {
public:
  PID(double soll, unsigned int maxsize, double *pid);
  PID(double soll, unsigned int maxsize);
  PID(double soll);
  PID(double *pid);
  PID(unsigned int maxsize);
  PID();
  ~PID();
  void setsoll(double soll);
  void setpid(double *pid);
  void setout(std::string name);
  void setmax(double max);
  void setmin(double min);
  void setdebug(double debug);
  double push_back(double ist);
  double operator<<(double data);
  const double ist();
  const double *coeff();
private:
  unsigned int _nvals;
  double _delta;
  double _delta2;
  double _soll;
  double _setpoint;
  unsigned int _maxsize;
  double _pid[3];
  double _integralstatic;
  double _max;
  double _min;
  void _process();
  void _proportional();
  void _integral();
  void _differential();
  std::ofstream _out;
  unsigned int _debug;
};

#endif
