#include <iostream>
#include <functional>
#include <string>
#include <stdio.h>
#include <string.h>
#include <memory>

#include <bcrypt.h>
#include <uv.h>

#include "uvpp/Loop.hpp"
#include "uvpp/GlobalLoop.hpp"
#include "helpers/bcrypt.hpp"

// TODO: handle errors.

void textadventure::bcrypt::generateSalt(
  int workfactor,
  std::function<void (std::string)> callback
) {
  textadventure::bcrypt::generateSalt(
    *uvpp::GlobalLoop::getLoop(),
    workfactor,
    callback
  );
}

void textadventure::bcrypt::generateSalt(
  uvpp::Loop& loop,
  int workfactor,
  std::function<void (std::string)> callback
) {
  loop.doWork(
    [workfactor]() {
      auto salt = new char[BCRYPT_HASHSIZE];
      bcrypt_gensalt(workfactor, salt);
      auto str = new std::string(salt);
      delete salt;
      return str;
    },
    [callback](void* result) {
      auto str = std::unique_ptr<std::string>(
        reinterpret_cast<std::string*>(result)
      );
      callback(*str);
    }
  );
}

void textadventure::bcrypt::performHash(
  std::string plaintext,
  std::string salt,
  std::function<void (std::string)> callback
) {
  textadventure::bcrypt::performHash(
    *uvpp::GlobalLoop::getLoop(),
    plaintext,
    salt,
    callback
  );
}

void textadventure::bcrypt::performHash(
  uvpp::Loop& loop,
  std::string plaintext,
  std::string salt,
  std::function<void (std::string)> callback
) {
  loop.doWork(
    [plaintext, salt]() {
      auto hash = new char[BCRYPT_HASHSIZE];
      char csalt[BCRYPT_HASHSIZE];
      auto csaltLength = salt.copy(csalt, salt.length(), 0);
      csalt[csaltLength] = '\0';

      auto cplaintext = plaintext.c_str();

      bcrypt_hashpw(cplaintext, csalt, hash);
      auto str = new std::string(hash);

      delete hash;

      return str;
    },
    [callback](void* result) {
      auto str = std::unique_ptr<std::string>(
        reinterpret_cast<std::string*>(result)
      );
      callback(*str);
    }
  );
}

void textadventure::bcrypt::performSaltAndHash(
  int workfactor,
  std::string plaintext,
  std::function<void (std::string)> callback
) {
  textadventure::bcrypt::performSaltAndHash(
    *uvpp::GlobalLoop::getLoop(),
    workfactor,
    plaintext,
    callback
  );
}

void textadventure::bcrypt::performSaltAndHash(
  uvpp::Loop& loop,
  int workfactor,
  std::string plaintext,
  std::function<void (std::string)> callback
) {
  textadventure::bcrypt::generateSalt(
    loop,
    workfactor,
    [callback, &loop, plaintext](std::string salt) {
    textadventure::bcrypt::performHash(
      loop,
      plaintext,
      salt,
      [callback](std::string hash) {
        callback(hash);
      }
    );
  });
}

void textadventure::bcrypt::verify(
  std::string plaintext,
  std::string hash,
  std::function<void (bool)> callback
) {
  textadventure::bcrypt::verify(
    *uvpp::GlobalLoop::getLoop(),
    plaintext,
    hash,
    callback
  );
}

void textadventure::bcrypt::verify(
  uvpp::Loop& loop,
  std::string plaintext,
  std::string hash,
  std::function<void (bool)> callback
) {
  textadventure::bcrypt::performHash(
    loop,
    plaintext,
    hash,
    [plaintext, hash, callback](std::string newHash) {
      callback(hash.compare(newHash) == 0);
    }
  );
}
