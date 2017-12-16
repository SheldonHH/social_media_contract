/**
 *  @file
 *  @copyright defined in eos/LICENSE.txt
 */
#include <eoslib/eos.hpp>
#include <eoslib/db.hpp>

/**
 *  @defgroup tictactoecontract Tic Tac Toe Contract
 *  @brief Defines the PvP tic tac toe contract example
 *  @ingroup examplecontract
 *  
 *  @details
 *
 *  For the following tic-tac-toe game:
 *  - Each pair of player can have 2 unique game, one where player_1 become host and player_2 become challenger and vice versa
 *  - The game data is stored in the "host" scope and use the "challenger" as the key
 *  
 *  (0,0) coordinate is on the top left corner of the board
 *  @code
 *                 (0,2)
 *  (0,0) -  |  o  |  x      where - = empty cell
 *        -  |  x  |  -            x = move by host
 *  (2,0) x  |  o  |  o            o = move by challenger
 *  @endcode
 * 
 *  Board is represented with number:
 *  - 0 represents empty cell
 *  - 1 represents cell filled by host 
 *  - 2 represents cell filled by challenger
 *  Therefore, assuming x is host, the above board will have the following representation: [0, 2, 1, 0, 1, 0, 1, 2, 2] inside the game object
 * 
 *  In order to deploy this contract:
 *  - Create an account called tic.tac.toe
 *  - Add tic.tac.toe key to your wallet
 *  - Set the contract on the tic.tac.toe account
 * 
 *  How to play the game:
 *  - Create a game using `create` action, with you as the host and other account as the challenger.
 *  - The first move needs to be done by the host, use the `move` action to make a move by specifying which row and column to fill.
 *  - Then ask the challenger to make a move, after that it's back to the host turn again, repeat until the winner is determined.
 *  - If you want to restart the game, use the `restart` action
 *  - If you want to clear the game from the database to save up some space after the game has ended, use the `close` action
 *  @{
 */

using namespace eosio;
namespace social {
  /**
   * @brief Data structure to hold game information
   */
  struct PACKED(social) {
    social() {};
    social(account_name challenger, account_name host):challenger(challenger), host(host), turn(host) {
      // Initialize board
      initialize_board();
    };
    account_name     author; // this also acts as key of the table
    account_name     voter;
    account_name     turn; // = account name of host/ challenger
    account_name     winner = N(none); // = none/ draw/ account name of host/ challenger
    uint8_t          board_len = 9;
    uint8_t          data; //
    



   struct post_action {
     account_name author;
     post_name    postid;
     account_name reply_to_author;
     int32_t      reply_to_id;
     uint8_t      author; /// index in notify list
     char[]       data; /// ignored, title is embedded within

     account_name get_author()const { return get_notify(author); }
    };

  struct vote_action {
     account_name voter;
     account_name author;
     post_name    postid;
     int32_t      vote_power;
  };

  struct post_record {
     uint64_t total_votes   = 0;
     uint64_t claimed_votes = 0;
     uint32_t created;

     post_record( uint32_t c = now() ):created(c){}
     static Name table_id() { return Name("post"); }
  };

  struct account {
     uint64_t social       = 0;
     uint64_t social_power = 0;
     int32_t  vote_power   = 0;
     uint32_t last_vote    = 0;

     static Name table_id() { return Name("account"); }
  };


  /**
   * @brief table to store list of games
   */ 
  using Social = eosio::table<N(social),N(social),N(social),social,uint64_t>;
}
/// @}
