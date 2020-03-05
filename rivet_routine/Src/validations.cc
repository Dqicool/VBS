		std::cout<<"-----------------------"<<std::endl;
		std::cout<<"lep_pairs_combs: "<<lep_pairs_comb.size()<<std::endl;
		std::cout<<"num:\t"<<"a1\ta2\tb1\tb2\t\tma\t\tmb\t\tmab"<<std::endl;
		for (int i = 0;i < lep_pairs_comb.size(); i++){
			double ma = ((lep_pairs_comb[i][0][0].momentum() + lep_pairs_comb[i][0][1].momentum()).mass() - Z_MASS);
			double mb = ((lep_pairs_comb[i][1][0].momentum() + lep_pairs_comb[i][1][1].momentum()).mass() - Z_MASS);
			std::cout<<i<<":\t"
			<<lep_pairs_comb[i][0][0].pid()<<"\t"<<lep_pairs_comb[i][0][1].pid()<<"\t"
			<<lep_pairs_comb[i][1][0].pid()<<"\t"<<lep_pairs_comb[i][1][1].pid()
			<<"\t"<<ma
			<<"\t\t"<<mb<<"\t\t"
			<<std::abs(ma)+std::abs(mb)<<std::endl;
		}

        if(Z1Z2.size() > 0){
			double m1 = (Z1Z2[0].mass() - Z_MASS);
			double m2 = (Z1Z2[1].mass() - Z_MASS);
			std::cout<<"Z1:\t\tZ2:\t\tZ12"<<std::endl;
			std::cout<<m1
			<<"\t\t"<<m2<<"\t\t"
			<<std::abs(m1)+std::abs(m2)<<std::endl;	
		}
		std::cout<<"-----------------------"<<std::endl;