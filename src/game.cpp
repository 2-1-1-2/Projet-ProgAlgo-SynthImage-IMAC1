#include "game.h"

Game::Game(Ball b, Corridor c, Racket r) {
  m_ball = Ball(b.getPos('X'), b.getPos('Y'), b.getPos('Z'));
  m_corridor = Corridor(c.getPos('X'),c.getPos('Y'), c.getPos('Z'),c.getSpeed()) ;
  m_racket = Racket(r.getPos('X'),r.getPos('Y'), r.getPos('Z'));
}


/* ********** G E T T E R S ********** */
Ball &Game::getBall() { return m_ball; }
Corridor &Game::getCorridor() { return m_corridor; }
Racket &Game::getRacket() { return m_racket; }


/* ********** S E T T E R S ********** */
