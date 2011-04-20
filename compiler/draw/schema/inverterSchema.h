#ifndef INVERTERSCHEMA_H
#define INVERTERSCHEMA_H


#include "blockSchema.h"

/**
 * An inverter : a special symbol corresponding to '*(-1)'
 * to create more compact diagrams
 */
class inverterSchema : public blockSchema
{

  public:
    friend schema* makeInverterSchema (const string& color);

    virtual void 	draw(device& dev);
  private:
     inverterSchema (const string& color);

};

#endif // INVERTERSCHEMA_H
