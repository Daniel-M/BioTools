class voxel_t
{
	private:

		int_t	itVoxelNumber; /*!< The number of the voxel_t.*/
		
		//std::set<index_t> useIndexes; /*!< The set of indexes that comprise the voxel_t.*/
		index_set_t useIndexes; /*!< The set of indexes that comprise the voxel_t.*/

		system_t ptrSystem; /*!< system_t pointer to the system assigned to the voxel_t. This allows to have many different systems in the same class */

	public:
		
		/*!\brief Standard constructor of voxel_t.*/
		voxel_t();

		/*!\brief Overloaded constructor of voxel_t that initializes by the system_t of the voxel_t*/
		voxel_t(system_t ptrSys);

		/*!\brief Overloaded constructor that receives a \c set of indexes and a \c system_t object.
		 * \param useIndexes_ The set of indexes to be assigned to the voxel_t.
		 * \param ptrSys The system to be assigned to the voxel_t.
		 */
		voxel_t(std::set<index_t> useIndexes_,system_t ptrSys);
		
		/*!\brief Overloaded constructor that receives an \c set of indexes and a \c system_t object.
		 * \param itVoxelNumber_ The number to be assigned to the voxel_t.
		 * \param useIndexes_ The set of indexes to be assigned to the voxel_t.
		 * \param ptrSys The system to be assigned to the voxel_t.
		 */
		voxel_t(int_t itVoxelNumber_, std::set<index_t> useIndexes_, system_t ptrSys);

		/*!\brief Retrieve the voxel_t's system by calling the index.
		 * \param inIndex_ The index to look on the voxel_t.
		 * \return system_t The system stored in the voxel_t.*/
		system_t operator[](index_t inIndex_);


		/*!\brief Sets the system_t of the voxel_t.
		 * \param ptrSys The system to be assigned to the voxel_t.*/
		voxel_t& operator=(const system_t ptrSys);

		/*!\brief Replace all indexes with one index.
		 * \param inIndex_ Index to replace all indexes.*/
		voxel_t& operator=(const index_t inIndex_);

		/*!\brief Set the set of indexes belongging to the voxel_t.
		 * \param useIndexes_ New set of indexes to fill the voxel_t.*/
		voxel_t& operator=(const std::set<index_t> useIndexes_);

		/*!\brief Add an index to the voxel_t.
		 * \param inIndex_ Index to be added to the voxel_t.*/
		voxel_t& operator+=(const index_t inIndex_);

		/*!\brief Insert an index to the voxel_t.
		 * \param inIndex_ The index to be inserted.
		 */
		void insert(index_t inIndex_);

		/*!\brief Set the system of the voxel_t.
		 * \param ptrSys The system to be assigned to the voxel_t. ptrSys is a pointer to a function of the form (x,dx,t) as \c libboost::odeint requires.
		 */
		void setSystem(system_t ptrSys);
		
		/*!\brief Evaluates the system of the voxel_t on the given time \c t by doing an increment of \c dt.
		 * \param[in][out] x The vector of values. Uses \c point_t because of the typedef \c std::vector<double>. 
		 * \param[in] t The instant of time to evaluate.
		 * \param[in] dt The time step.
		 * */
		void evalSystem(point_t& x, double t, double dt);
		void evalSystem(std::vector<chem_t>& x, double t, double dt);

		/*!\brief Get the number of the voxel_t.
		 * \return The number of the voxel_t.*/
		int_t getVoxelNumber();

		/*!\brief Check if the index exist on the voxel_t.
		 * \param inIndex The index to be searched within the voxel_t.
		 * \return 0 for no findings, else for findings.*/
		int_t count(index_t inIndex_);

		/*!\brief Get the system_t stored on the voxel_t.
		 * \return The system assigned to the voxel_t.*/
		system_t getSystem();

};
