/**
 *  @file
 *  @copyright defined in eos/LICENSE.txt
 */
#include <eoslib/eos.hpp>
#include <eoslib/db.hpp>



using namespace eosio;
namespace social {

  struct PACKED(social) {
    social() {};
    social(account_name challenger, account_name host):challenger(challenger), host(host), turn(host) {
    };

    



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
