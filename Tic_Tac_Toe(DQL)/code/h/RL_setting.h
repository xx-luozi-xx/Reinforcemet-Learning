
#pragma once

namespace RL{
const char* SAVING_PATH = "./save/";
const int GAME_ROUND = 50000; // game rounds (training rounds)
const double LEARNING_RATE = 0.001;
const double EPSILON = 0.7;// if rand(0,1)<= epsilon then do random action
const int BATCH = 1000;


/**
 * @brief 
 *         TEST_ID == "0"时，使用EPSILON从1下降的对等对抗
 *         TEST_ID == "1"时，对白棋恒使用EPSILON=1的随机，对黑棋先EPSILON=0.1的学习，再EPSILON=0的测试
 * 
 */
const char* TEST_ID = "0";

}

