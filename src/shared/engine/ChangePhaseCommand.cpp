// ChangePhaseCommand.cpp
#include "ChangePhaseCommand.h"

namespace engine {

    // Constructor
    ChangePhaseCommand::ChangePhaseCommand(state::PlayerId authorPlayer, state::Phase phase) {

    }

    // Destructor
    ChangePhaseCommand::~ChangePhaseCommand() {
    }

    // Execute method
    void ChangePhaseCommand::execute(state::GameState &state) {
    }

    bool ChangePhaseCommand::check(state::GameState &state) {
        return Command::check(state);
    }


} // namespace engine
