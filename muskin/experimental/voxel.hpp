class voxel
{
	private:

		int_t	itVoxelNumber; /*!< The number of the voxel.*/
		
		std::set<index_t> useIndexes; /*!< The set of indexes that comprise the voxel.*/

		system_t stSystem; /*!< system_t object of the voxel.*/


	public:
		
		/*!\brief Standard constructor of Voxel.*/
		voxel();

		/*!\brief Overloaded constructor that receives a \c set of indexes and a \c system_t object.
		 * \param useIndexes_ The set of indexes to be assigned to the voxel.
		 * \param stSystem_ The system to be assigned to the voxel.
		 */
		voxel(std::set<index_t> useIndexes_,system_t stSystem_);
		
		/*!\brief Overloaded constructor that receives an \c set of indexes and a \c system_t object.
		 * \param itVoxelNumber_ The number to be assigned to the voxel.
		 * \param useIndexes_ The set of indexes to be assigned to the voxel.
		 * \param stSystem_ The system to be assigned to the voxel.
		 */
		voxel(int_t itVoxelNumber_, std::set<index_t> useIndexes_, system_t stSystem_);

		/*!\brief Retrieve the voxel's system by calling the index.
		 * \param inIndex_ The index to look on the voxel.
		 * \return system_t The system stored in the voxel.*/
		system_t operator[](index_t inIndex_);


		/*!\brief Sets the system_t of the voxel.
		 * \param stSystem_ The system to be assigned to the voxel.*/
		voxel& operator=(const system_t stSystem_);

		/*!\brief Replace all indexes with one index.
		 * \param inIndex_ Index to replace all indexes.*/
		voxel& operator=(const index_t inIndex_);

		/*!\brief Set the set of indexes belongging to the voxel.
		 * \param useIndexes_ New set of indexes to fill the voxel.*/
		voxel& operator=(const std::set<index_t> useIndexes_);

		/*!\brief Add an index to the voxel.
		 * \param inIndex_ Index to be added to the voxel.*/
		voxel& operator+=(const index_t inIndex_);

		/*!\brief Insert an index to the voxel.
		 * \param inIndex_ The index to be inserted.
		 */
		void insert(index_t inIndex_);

		/*!\brief Set the system of the voxel.
		 * \param stSystem_ The system to be assigned to the voxel.
		 */
		void setSystem(system_t stSystem_);


		/*!\brief Get the number of the voxel.
		 * \return The number of the voxel.*/
		int_t getVoxelNumber();

		/*!\brief Check if the index exist on the voxel.
		 * \param inIndex The index to be searched within the voxel.
		 * \return 0 for no findings, else for findings.*/
		int_t count(index_t inIndex_);

		/*!\brief Get the system_t stored on the voxel.
		 * \return The system assigned to the voxel.*/
		system_t getSystem();

};
