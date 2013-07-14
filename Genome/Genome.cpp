////////////////////////////////////////////////////////////////////////////////
// Filename: Genome.cpp
// Dependencies
// Description: Handles reading in data from 23andme raw data files and 
// saving it into data structures
////////////////////////////////////////////////////////////////////////////////
#include "Genome.h"
#include <iomanip>

Genome::Genome()
{
	m_chromosomes = new Chromosome[CHROMOSOME_COUNT]; //Each array element stores a chromosome
}

Genome::~Genome()
{

}

void Genome::Shutdown()
{
	for(int i = 0; i < CHROMOSOME_COUNT; i++)
	{
		m_chromosomes[i].Shutdown();
	}

	delete[] m_chromosomes;
	m_chromosomes = 0;
}

bool Genome::LoadFromBinFile(char* fileName)
{
	if(!fileName)
		return false;

	stringstream streamData;

	streamData << "../Genome/" << fileName << ".bin";

	ifstream file;

	file.open(streamData.str(), ios::in, ios::binary);

	if(!file) return false;

	file.seekg(0, ios::beg);

}

bool Genome::SaveToBinFile(char* fileName)
{
	if(!fileName)
		return false;

	stringstream streamData;

	streamData << "../Genome/" << fileName << ".bin";

	ifstream file;

	file.open(streamData.str(), ios::in, ios::binary);

	if(!file) return false;

	file.seekg(0, ios::beg);


}

bool Genome::LoadFromTextFile(char* fileName)
{
	// No file name was passed.
	if(!fileName)
		return false;

	stringstream ss;

	// Filepath.
	ss << "../Genome/" << fileName << ".txt";

	ifstream file;

	// Open the file.
	file.open(ss.str(), ios::in);

	// Check if the file exists.
	if(!file) return false;

	// Reset file to beginning.
	file.clear();
	file.seekg(0, ios::beg);

	char input;
	int currentChromo = 0;

	file.get(input);
	while(!file.eof())
	{
		// Comment found. Skip to the end of the line.
		if(input == '#')
		{
			while(input != '\n')
			{
				file.get(input);
			}
		}
		else
		{
			// snp rsid can either start with rs or i.
			if(input == 'r')
			{
				// Move pass s.
				file.get(input);
				
				SNP snp;
				snp.genotype[0] = ' ';
				snp.genotype[1] = ' ';

				string chromoIndexStr;

				string genotypeStr;

				file >> snp.rsid >> chromoIndexStr;
				
				// If the number is actually a number.
				if(IsNumber(chromoIndexStr))
				{
					// Convert to integer.
					int chromoIndex = stoi(chromoIndexStr);
					file >> snp.position >> genotypeStr;

					// If the index is valid. (File starts at 1).
					if(chromoIndex < CHROMOSOME_COUNT + 1)
					{
						// Load in genotype of up to two chars.
						if(genotypeStr.length() <= 2)
						{
							for(unsigned int i = 0; i < genotypeStr.length(); i++)
							{
								snp.genotype[i] = genotypeStr[i];
							}
						}

						// Load the snp into the chromosome.
						m_chromosomes[chromoIndex - 1].AddSNP(snp);

						// Print the loading percentage.
						if(chromoIndex != currentChromo)
						{
							system("cls");
							currentChromo = chromoIndex;
							float loadPercent = (float)chromoIndex / (float)(CHROMOSOME_COUNT);
							cout << "Loading: " << fixed << setprecision(2) << 100 * loadPercent << "%";
							cout << "\n";
						}
					}
				}
			}
		}

		file.get(input);
	}

	// Close the file.
	file.close();

	return true;
}

void Genome::Print(unsigned int x)
{
	cout << "\n\n";
	for(int i = 0; i < CHROMOSOME_COUNT; i++)
	{
		cout << "Chromosome: " << i + 1 << "\n";
		m_chromosomes[i].PrintSNP(x);
	}
}

Chromosome::Chromosome()
{
}

Chromosome::~Chromosome()
{
}

void Chromosome::Shutdown()
{
	m_snp.clear();
}

void Chromosome::AddSNP(SNP& snp)
{
	m_snp.push_back(snp);
}

void Chromosome::PrintSNP(unsigned int x)
{
	for(unsigned int i = 0; i < m_snp.size(); i++)
	{
		if(i % x == 0)
		{
			cout << "\t" << m_snp[i].genotype[0] << m_snp[i].genotype[1] << "\n";
		}
	}
}

bool IsNumber(const std::string& s)
{
    return !s.empty() && s.find_first_not_of("0123456789") == std::string::npos;

}

