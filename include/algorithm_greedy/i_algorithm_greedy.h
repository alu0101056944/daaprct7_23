#ifndef ALGORITHM_GREEDY_H
#define ALGORITHM_GREEDY_H

class IAlgorithmGreedy {
public:
  virtual ~IAlgorithmGreedy() {}

  virtual void preprocess() = 0;
  virtual bool hasCandidates() = 0;
  virtual bool isAtSolution() = 0;
  virtual void selectBestCandidate() = 0;
  virtual bool validCandidate() = 0;
  virtual void addCandidate() = 0;
  virtual void print() = 0;
private:
};

#endif
