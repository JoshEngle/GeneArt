////////////////////////////////////////////////////////////////////////////////
// Filename: Genome.h
////////////////////////////////////////////////////////////////////////////////
#ifndef _GENOME_H
#define _GENOME_H

#include <fstream>
#include <sstream>
#include <iostream>
#include <vector>
#include <algorithm>

#define CHROMOSOME_COUNT	22

#define NONE		0
#define A			1
#define C			2
#define G			3
#define T			4

#define RS			5
#define I			6

using namespace std;

bool IsNumber(const string& s);

struct SNP
{
public:
	unsigned long	rsid;
	unsigned int	position;
	// [A, C], [A, NONE]
	char			genotype[2];
};

class Chromosome
{
public:
	Chromosome();
	~Chromosome();
	void AddSNP(SNP&);							// Add to m_snp. Provide snp address.
	void Shutdown();							// Clear m_snp.
	void PrintSNP(unsigned int x);				// Print every x entry.
private:
	vector<SNP>	 m_snp;
};

class Genome
{
public:
	Genome();
	~Genome();
	bool LoadFromTextFile(char* fileName);		// Load from plain text file.
	void Shutdown();							// Free all memory associated with m_chromosomes.
	void Print(unsigned int x);					// Print the genome of every x snp..
private:
	Chromosome*		m_chromosomes;				// Array of size CHROMOSOME_COUNT.
};

#endif