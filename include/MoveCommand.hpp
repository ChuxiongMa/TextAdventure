/*
 * MoveCommand.h
 *
 *  Created on: Oct 29, 2015
 *      Author: andrew
 */

#ifndef SRC_MOVECOMMAND_H_
#define SRC_MOVECOMMAND_H_

#include "Command.hpp"
#include "Room.hpp"

namespace textadventure {

  class MoveCommand : Command {
  public:
    using Command::Command;
    MoveCommand(Door);
    virtual void execute() override;
  private:
    Door door;
  };

} /* namespace textadventure */

#endif /* SRC_MOVECOMMAND_H_ */
