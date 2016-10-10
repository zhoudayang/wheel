//
// Created by zhouyang on 2016/10/11.
//

#include "HashTableTest.h"

#include "hash_table.h"

void run_all_tests() {
    test_add_exists();
    test_probing();
    test_get();
    test_remove();
}

void test_add_exists() {
    HashTable states(100);

    HashObject tx;
    tx.setKey("Texas");
    tx.setValue("Austin");

    states.Add(&tx);

    assert(states.Exists("Texas"));
}

void test_probing() {
    // setting high load to force collisions
    HashTable states(8);

    HashObject tx;
    tx.setKey("Texas");
    tx.setValue("Austin");

    HashObject ca;
    ca.setKey("California");
    ca.setValue("Sacramento");

    HashObject nm;
    nm.setKey("New Mexico");
    nm.setValue("Santa Fe");

    HashObject fl;
    fl.setKey("Florida");
    fl.setValue("Tallahassee");

    HashObject oregon;
    oregon.setKey("Oregon");
    oregon.setValue("Salem");

    HashObject wa;
    wa.setKey("Washington");
    wa.setValue("Olympia");

    HashObject ut;
    ut.setKey("Utah");
    ut.setValue("Salt Lake City");

    HashObject ny;
    ny.setKey("New York");
    ny.setValue("Albany");

    HashObject mn;
    mn.setKey("Minnesota");
    mn.setValue("St. Paul");

    states.Add(&tx);  // 1
    states.Add(&ca);  // 0
    states.Add(&nm);  //
    states.Add(&fl);
    states.Add(&oregon);
    states.Add(&wa);
    states.Add(&ut);
    states.Add(&ny);
    states.Add(&mn);

    //  Texas:1
    //  California:0
    //  New Mexico:5
    //  Florida:5
    //  Oregon:4
    //  Washington:0
    //  Utah:6
    //  New York:7
    //  Minnesota:6

    //  0: California:Sacramento
    //  1: Texas:Austin
    //  2: Washington:Olympia
    //  3: New York:Albany
    //  4: Oregon:Salem
    //  5: New Mexico:Santa Fe
    //  6: Florida:Tallahassee
    //  7: Utah:Salt Lake City

    assert(states.Exists("California"));
    assert(states.Exists("New Mexico"));
    assert(states.Exists("Florida"));
    assert(!states.Exists("Minnesota"));  // no room
}

void test_get() {
    HashTable states(100);

    HashObject tx;
    tx.setKey("Texas");
    tx.setValue("Austin");

    states.Add(&tx);

    assert(states.Get("Texas") == "Austin");
}

void test_remove() {
    HashTable states(100);

    HashObject tx;
    tx.setKey("Texas");
    tx.setValue("Austin");

    states.Add(&tx);

    assert(states.Exists("Texas"));

    states.Remove("Texas");

    assert(!states.Exists("Texas"));
}